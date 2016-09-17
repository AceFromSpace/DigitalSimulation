#ifndef PROJECT5_GENERATORS_H_
#define PROJECT5_GENERATORS_H_
#include <math.h>
#include <fstream>

//Contains all generators and statiscs of them
class Generators
{
public:
	Generators(int number_of_sim, int start_point);
	~Generators();
	
	void seeds_Generator(int start_point);//generates seeds for every generator
	int TPW_Generator();
	int TPO_Generator();
	int TPIO_Generator(int new_TPW);
	int TPD_Generator();
	int TPP_Generator();//TPP-time per processor
	double TPG_Generator(double lambda);
 	void save_stats_to_file(); // makes histgram of drawed values for every generator
	void go_to_the_next_simulation();

private:
	int number_of_simulations;
	int current_number_of_sim;
	int TPW;
	int TPO;
	int TPIO;
	int TPD;
	int TPG_uni; 
	int TPP; // for processor queues drawing (0:9)
	int** SEEDS;
	//histograms
	int* TPW_hist;
	int* TPO_hist;
	int* TPIO_hist;
	int* TPD_hist;
	int* TPG_hist;
	int* TPP_hist;

};

#endif