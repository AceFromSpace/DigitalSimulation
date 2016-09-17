#ifndef PROJECT5_PLANNER_H_
#define PROJECT5_PLANNER_H_
#include "agenda.h"
#include "deviceIO.h"
#include "processor.h"
#include "generators.h"
#include "statistics.h"
//Main class of simulation system . Contain every other classes . This class manage whole system.
//Represents single simulation



class Planner
{
public:
	Planner(double lamb,bool mode, Generators* gener,statistics* stat,int number_of_proc);
	~Planner();
	
	void main_loop();

private:
	
	std::vector<DeviceIO*> Devices;
	Processor *Processor_main;
	Process *current;
	Agenda *list;
	Generators* gen;
	statistics* stats;
	double clock;
	double lambda;
	int number_of_simulations;
	int current_number_of_simulation;
	bool chosen_mode;
	int number_of_processes;
};
#endif
