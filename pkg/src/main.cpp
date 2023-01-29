#include<Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"EuropeanOption.h"
#include"getVecMean.h"
#include"getVecStdDev.h"

using namespace Rcpp;
using std::vector;

// [[Rcpp::export]]
double getEuropeanCallPrice(
  int nInt,
  double Strike,
  double Spot,
  double Vol,
  double Rfr,
  double Expiry,
  double Barrier,
  int nReps = 1000){

	// set the seed
	srand( time(NULL) );

	// create a new instance of a class
	EuropeanOption myEuropean(nInt, Strike, Spot, Vol, Rfr, Expiry, Barrier);

	// call the method to get option price
	double price = myEuropean.getEuropeanCallPrice(nReps);
	
	// return option price  
	return price;
}
