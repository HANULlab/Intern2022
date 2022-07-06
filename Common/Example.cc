#include "Functions.hh"//Load the custom-made headerfile.
void Example(){
	cout<<"GenGaus() generates random gaussian distribution."<<endl;
	cout<<"FitGaus() Fits the data with gaussian function."<<endl;
	cout<<"FitPMT(TString filename) Fits PMT respose spectrum"<<endl;
}


void GenGaus()
{
	gRandom->SetSeed();//Set Random seed
	TF1* gausf= new TF1("gaUf","Gausf",-10,10,3);//gausf is a TF1* class, which is defined as "Gausf(double* x,double* par)" defined in Function.hh. The key to call gausf is 'gaUf'. 
	gausf->SetParameters(1,1,2);//set peak, mean, sigma of the gausf.
	double x_;
	TString name= "gaussian";
	TString dir="./rootfiles/";
	TFile* file = new TFile(dir+name+".root","RECREATE");//make file.
	TTree* tree = new TTree("tree","tree");//make tree.
	tree->Branch("x",&x_,"x/D");//attach x_ to branch named "x".
	int ent = 10000;
	for(int i=0;i<ent;i++)
	{
		x_=gausf->GetRandom();//get random from gausf.
		tree->Fill();//fill the tree.
	}
	file->Write();//write the file.
	cout<<"file "<<name<<" written at "<<dir<<endl;
}
void FitGaus()
{
	TF1* gausf= new TF1("gaUf","Gausf",-10,10,3);
	double x_;
	TString name= "gaussian";
	TString dir="./rootfiles/";
	TFile* file = new TFile(dir+name+".root","read");//load the file in read mode.
	TTree* tree = (TTree*)file->Get("tree");//get the tree from the file.
	TH1D* h = new TH1D("gh","gaussian_histogram",200,-10,10);//declare 1D histogram, with 200 bins, ranging from -10 to 10.
	tree->Draw("x>>gh");	//Fill all x to histogram. histogram should be called by 'key(gh)'.
	
	/*does the same job as tree->Draw() method.
	tree->SetBranchAddress("x",&x_);//Assign the branch 'x' in file to token 'x_'
	int ent = tree->GetEntries();
	for(int i=0;i<ent;++i){
		tree->GetEntry(i);//Get data in branch. As branch 'x' is assigned to 'x_', 'x_' will get the data. 
		h->Fill(x_);//Fill x_ into histogram.
	}
*/	

	gausf->SetParLimits(0,100,1000);//Limit the parameter range used in fitting. since par0 is peak, peak is limited from 100 to 1000.
	gausf->SetParLimits(1,-2,3);
	gausf->SetParLimits(2,0.1,10);
	h->Fit("gaUf");//Entry should no be the 'token(gausf)', but 'key' of the function.
	double peak = gausf->GetParameter(0);
	double mean = gausf->GetParameter(1);
	double sigma = gausf->GetParameter(2);
	cout<<"peak, mean, sigma is: "<<peak<<" , "<<mean<<" , "<<sigma<<endl;
}
void FitPMT(TString filename){

	TFile* file = new TFile(filename,"read");//load the file in read mode.
	TTree* tree = (TTree*)file->Get("data");//get the tree from the file.
	TH1D* h = new TH1D("pmth","PMT Spectrum",400,100,500);
	tree->Draw("ADC[0]>>pmth");	//
	TF1* fg = new TF1("PMT","PMTf", 0,1000,8);
	fg->SetParLimits(0,170,190);
	fg->SetParLimits(1,0.1,5);
	fg->SetParLimits(2,0.5,5);
	fg->SetParLimits(3,30,45);
	fg->SetParLimits(4,6,20);
	fg->SetParLimits(5,30000,1000000);
	fg->SetParLimits(6,0.1,100);
	fg->SetParLimits(7,300,500);
	fg->SetRange(150,270);
  h->Fit("PMT","R");
	double par[8];
	for(int i=0;i<8;i++){
		par[i]=fg->GetParameter(i);
	}
	TF1* ped_f = new TF1("pedf","Ngausf",0,1000,3);
	double pp=par[5]*Poison_dist(par[2],0);
	ped_f->SetParameters(par[0],par[1],pp);
	ped_f->SetLineColor(kBlack);
	ped_f->Draw("SAME");
	TF1* bg_f = new TF1("bgf","Backgroundf",0,1000,3);
	bg_f->SetParameters(par[0],par[6],par[7]);
	bg_f->SetLineColor(kBlack);
	bg_f->Draw("SAME");
	
	double spp = par[5]*Poison_dist(par[2],1); 
	TF1* single_f = new TF1("singlef","Ngausf",0,1000,3);
	single_f->SetParameters(par[0]+par[3],par[4],spp);
	single_f->SetLineColor(kBlue);
	single_f->Draw("SAME");
	double dpp = par[5]*Poison_dist(par[2],2); 
	TF1* double_f = new TF1("doublef","Ngausf",0,1000,3);
	double_f->SetParameters(par[0]+2*par[3],sqrt(2)*par[4],dpp);
	double_f->SetLineColor(kGreen);
	double_f->Draw("SAME");
}

