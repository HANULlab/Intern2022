double Gaus(double x, double peak,double mean,double sigma){
	double nm = (x-mean)/sigma;
	return peak*exp(-nm*nm/2);
}
double Gausf(double* x,double* par){
	return Gaus(x[0],par[0],par[1],par[2]);
}
double Ngaus(double x, double m, double s){//Normalized Gaussian 
 return (exp(-(x-m)*(x-m)/(2*s*s)))/sqrt(2*TMath::Pi()*s*s);
}
double Ngausf(double* x,double* par){
	return Ngaus(x[0],par[0],par[1])*par[2]; 
}
double Poison_dist(double lambda,double x){
	double val=0;
		val=exp(-lambda)*pow(lambda,x)/TMath::Gamma(x+1);
	return val;
}
double Background(double x, double ped,double slope,double peak){
	double val=0;
	if(x<ped){
	}
	else{
		val+=exp((ped-x)/slope)*peak;
	}
	return val;
}
double Backgroundf(double* x,double* p){
	return Background(x[0],p[0],p[1],p[2]);
}
double PMTf(double* x,double* par){
	double ped_mean=par[0];
	double ped_width=par[1];
	double lambda=par[2];
	double tot = par[5];
	double ped_peak=Poison_dist(lambda,0)*tot;
	double single_gain=par[3];
	double single_width=par[4];
	double single_peak=Poison_dist(lambda,1)*tot;
//	double double_width=single_width*sqrt(2);
	double double_width=sqrt(2)*par[4];
	double double_peak=Poison_dist(lambda,2)*tot;
	double bg = Background(x[0],ped_mean,par[6],par[7]);
	return Ngaus(x[0],ped_mean,ped_width)*ped_peak + Ngaus(x[0],single_gain+ped_mean,single_width)*single_peak +Ngaus(x[0],single_gain*2+ped_mean,double_width)*double_peak+bg;
}

