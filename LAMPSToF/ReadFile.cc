TString runs[10] = {"ped","015cm","030cm","045cm","060cm","075cm","090cm","105cm","120cm","135cm"};

void ReadFile(){
	TString filename_base = "Sr90_";
	TFile* files[10];
	TTree* trees[10];
	TCanvas* c1 = new TCanvas("c1","c1",1500,700);
	c1->Divide(4,3);
	TH1* hist[10] ;
	TString ents = "qdc[10]>>";
	for(int i=0;i<10;++i){
		TString ht = Form("hist%d",i);
		hist[i] = new TH1D(ht,ht,100,0,1000);
	}
	for(int i = 0;i<10;++i){
		TString ht = Form("hist%d",i);
		TString filename = filename_base+runs[i]+".root";
		files[i]= new TFile(filename,"read");
		trees[i]=(TTree*)files[i]->Get("tree");
		c1->cd(i+1);
		cout<<ents+ht<<endl;
		trees[i]->Draw(ents+ht,"");
//		hist[i]->SetLineColor(i);
//		hist[i]->Draw();
	}


}

