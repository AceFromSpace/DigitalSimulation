#include "planner.h"
#include <iostream>
#include <fstream>
#include <string>



Planner::Planner(double lamb,bool mode,Generators* gener,statistics* stat,int number_of_proc):lambda(lamb)
{
	number_of_processes = number_of_proc;
	stats = stat;
	list = new Agenda();
	for (int i = 0; i < 10; i++)
	{
		Devices.push_back(new DeviceIO());
	}
	gen = gener;
	Processor_main = new Processor(gen);
	clock = 0.0;
	chosen_mode = mode;
	current_number_of_simulation = 0;

	
	
}
Planner::~Planner()
{
	delete Processor_main;

	std::vector<DeviceIO*> temp_vector;
	Devices.swap(temp_vector);
	delete list;
} 
void Planner::main_loop()
{
	int i = 0;
	int starting_phase = 50;
	int total_time_of_using_processor = 0;
	int finish_time = 1400000;
	bool stop_counting_finished_process = false;
	bool stop_counting_time = false;

	
		Process* first = new Process(list, Processor_main, Devices, clock, gen, lambda);
		if (chosen_mode)first->set_mode();
		first->activate(0);

		while (true)
		{
			current = list->return_first()->return_proc();
			clock = list->return_first()->get_event_time();
			list->delete_first_event();
			if (chosen_mode)std::cout << "planner clock: " << clock << std::endl;
			current->set_clock(clock);
			if (chosen_mode)std::cout << "phase: " << current->return_phase() << std::endl;
			if (chosen_mode)std::cout << "number: " << current->return_number() << std::endl;
			current->execute();
			if (chosen_mode)std::cout << "Queue:" << std::endl;
			if (chosen_mode)list->show_queue();
			if (current->is_terminated())
			{

				if ((i >= starting_phase)&&!stop_counting_finished_process)
				{
					stats->get_stats(current, (i - starting_phase));
					Process::start_counting_time_of_processor();
					
				}
				i++;
				delete current;
				
				if (i > (number_of_processes - 1 + starting_phase))stop_counting_finished_process = true;;
				
			}
			if (clock > finish_time )
			{
				if (chosen_mode)std::cout << "Stop counting time of using processor" << std::endl;
				Process::stop_counting_time_of_processor();
				stop_counting_time = true;
			}
			if (stop_counting_finished_process&&stop_counting_time)break;
			if (chosen_mode)getchar();
			
		}
		
	 
		double procent = static_cast<double>(Process::return_total_time_of_using_processor()) / finish_time;
		
		cout << "Procent of using procesor: " << procent << endl;
		double capacity = static_cast<double>(i) / finish_time;
		cout << "Average capacity of proces : " << capacity <<"process/secound" <<endl;
		double time_of_waiting_to_devices = Process::return_average_TODE();
		cout << "Average time of waiting in queues to deviceIO  : " << time_of_waiting_to_devices << endl;
		cout << "Average time of waiting in queues to processor  : " << stats->return_average_TOW_per_simulation() << endl;
		cout << "Average time of processing: " << stats->return_average_TOL_per_simulation() << endl;
		cout << "Maximal time of waiting in queues to processor: " << stats->return_max_per_simulation() << endl;
		stats->get_capacity_usage_TODE(capacity, procent,time_of_waiting_to_devices);
		Process::reset_total_time_of_using_processor();
		gen->save_stats_to_file();
		

}




