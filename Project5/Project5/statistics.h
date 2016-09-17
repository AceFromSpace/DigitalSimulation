#ifndef PROJECT5_STATISTICS_H_
#define PROJECT5_STATISTICS_H_
#include "process.h"
#include <iostream>
using namespace std;
// All statistics of Time of waitng ,time of processing , capacity , processor usage ,maximal time of waiting
class statistics
{
public:
	statistics(int number_of_sims,int number_of_simulation_per_l,int number_of_proc);
	~statistics();

	void get_stats(Process* proc, int number);
	void get_capacity_usage_TODE(double cap, double usa, double TOD);
	void increase_current_number_of_simulation();//goes to the next simulation
	void average(int k);// counting average time of waiting per simulation
	double average_of_average_lambda();// counting average time of waiting per lambda 
	double average_of_average_processing(int k);//counting average time of processing per lambda 

	double return_average_capacity(int k);
	double return_average_usage(int k);
	double return_average_TODE(int k);
	double return_average_max(int k);
	double return_average_TOW_per_simulation();
	double return_average_TOL_per_simulation();
	double return_max_per_simulation();
	void save_to_file_each_TOW();//saves to file every time of waiting in queue to processor
	void save_to_file_for_lamdba();//saves to file average time of wainting per simulation and average of this values
	void save_to_file_all();//saves to file every parameter and his average 
	void save_to_file_averages_only(); //saves only averages for every parameter
	void save_to_file_max();//save maximal time of waitning of every simulation and his average per lambda 
	void average_time_for_lambda(int k);
	void average_time_of_processing(int k);

private:
	int number_of_simulation_per_lambda;
	int total_number_of_simulations;
	int current_number_of_simulation;
	int number_of_processes;

	double** tab_of_TOL;//tab of time of life(processing)
	double** tab_of_TOW;// tab of time of waiting in queue to processor
	double* tab_of_max; //tab of maximal time of waiting in queue to processor
	double* average_tab_of_max;
	double* average_tab_of_TOW;
	double* tab_of_time_per_lambda;
	double* tab_of_time_of_processing;
	double* average_tab_of_time_of_processing;
	double* average_per_lambda;
	double* tab_of_capacity;
	double* average_tab_of_capacity;
	double* tab_of_processor_usage;
	double* average_tab_of_usage;
	double* tab_of_TODE; //tab of time of waiting to queue to devices
	double* average_tab_of_TODE;

};

#endif