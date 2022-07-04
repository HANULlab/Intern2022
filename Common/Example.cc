#include "Functions.hh"
void Example(){
	cout<<"GenGaus() generates random gaussian distribution."<<endl;
	cout<<"FitGaus() Fits the data with gaussian function."<<endl;

}


void GenGaus()
{
	gRandom->SetSeed();
	TF1* gausf= new TF1("gaUf","Gausf",-10,10,3);
	gausf->SetParameters(1,1,2);
	//	Int_t nbeam=100;
	double x;
	TString name= "gaussian";
	TString dir="./rootfiles/";
	TFile* file = new TFile(dir+name+".root","RECREATE");
	TTree* tree = new TTree("tree","tree");
	tree->Branch("x",&x,"x/D");
	int ent = 10000;
	for(int i=0;i<ent;i++)
	{
		x=gausf->GetRandom(); tree->Fill();
	}
	file->Write();
	cout<<"file "<<name<<" written at "<<dir<<endl;
}
void FitGaus()
{
	TF1* gausf= new TF1("gaUf","Gausf",-10,10,3);
	double x;
	TString name= "gaussian";
	TString dir="./rootfiles/";
	TFile* file = new TFile(dir+name+".root","read");
	TTree* tree = (TTree*)file->Get("tree");
	TH1D* h = new TH1D("gh","gaussian_histogram",200,-10,10);
	tree->Draw("x>>gh");	
	gausf->SetParLimits(0,100,1000);
	gausf->SetParLimits(1,-2,3);
	gausf->SetParLimits(2,0.1,10);
	h->Fit("gaUf");
	double peak = gausf->GetParameter(0);
	double mean = gausf->GetParameter(1);
	double sigma = gausf->GetParameter(2);
	cout<<"peak, mean, sigma is: "<<peak<<" , "<<mean<<" , "<<sigma<<endl;
}
