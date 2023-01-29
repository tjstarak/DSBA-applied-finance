#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"EuropeanOption.h"


//definition of constructor
EuropeanOption::EuropeanOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
	double barrier_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		barrier = barrier_;
		generatePath();
}

//method definition
void EuropeanOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}

//method definition
double EuropeanOption::isBarrierHit(){

	// double runningSum = 0.0;
	double barrierHit = 0.0;

	for(int i = 0; i < nInt; i++){
		// runningSum += thisPath[i];
		if (thisPath[i] < barrier) {
			barrierHit = 1.0;
			break;
		}
	}

	// return runningSum/double(nInt);
	return barrierHit;
}


//method definition
void EuropeanOption::printPath(){

	for(int i = 0;  i < nInt; i++){

		std::cout << thisPath[i] << "\n";

	}

}

//method definition
double EuropeanOption::getEuropeanCallPrice(int nReps){

	double rollingSum = 0.0;

	for(int i = 0; i < nReps; i++){
		generatePath();
		double finalPrice = 0;
		finalPrice = thisPath[nInt - 1] * (1 - isBarrierHit());
		rollingSum += (finalPrice > strike) ? (finalPrice - strike) : 0;
	}

	return exp(-r*expiry)*rollingSum/double(nReps);

}

//overloaded operator ();
double EuropeanOption::operator()(char char1, char char2, int nReps){
	if ((char1 == 'E') & (char2 =='C'))      return getEuropeanCallPrice(nReps);
	else return -99;
}
