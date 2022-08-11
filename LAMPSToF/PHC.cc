void PHC(){
	TFile* file = new TFile("Intern_2022_Cosmic.root","read");
	TTree* tree = (TTree*)file->Get("tree");
	TH2D* hist = new TH2D("BTOF_Timing","BTOF_Timing",100,0,10,100,-5,7.5);
	tree->Draw("0.025*(tdc[10]-tdc[4]):(qdc[10]-85)/100>>BTOF_Timing","tdc[10]>0","col");
	double rm = 0.2;
	TF1* f = new TF1("func","[0]/sqrt(x-[1])+[2]",rm,10);
		
	f->SetParLimits(0,0.1,5);
	f->SetParLimits(1,-1,rm);
	f->SetParLimits(2,-1.5,2);

//	hist->Fit("func","R");
	hist->GetXaxis()->SetTitle("Edep[arb]");
	hist->GetYaxis()->SetTitle("Time[ns]");
		/*f->SetRange(11,1000);
	f->SetParameter(0,100);
	f->SetParameter(1,10);
	f->SetParameter(2,0);
	f->Draw("same");
	*/
}
