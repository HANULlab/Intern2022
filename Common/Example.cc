#include "Functions.hh"//Load the custom-made headerfile.
void Example(){
	cout<<"GenGaus() generates random gaussian distribution."<<endl;
	cout<<"FitGaus() Fits the data with gaussian function."<<endl;

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
