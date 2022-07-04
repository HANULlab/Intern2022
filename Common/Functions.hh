double Gaus(double x, double peak,double mean,double sigma){
	double nm = (x-mean)/sigma;
	return peak*exp(-nm*nm/2);
}
double Gausf(double* x,double* par){
	return Gaus(x[0],par[0],par[1],par[2]);
}
