#include<vector>

class EuropeanOption{
public:

	//constructor
	EuropeanOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_,
		double barrier
		);

	//destructor
	~EuropeanOption(){};

	//methods
	void generatePath();
	double isBarrierHit();
	void printPath();
	double getEuropeanCallPrice(int nReps);
	double operator()(char char1, char char2, int nReps);
	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double barrier;

};
