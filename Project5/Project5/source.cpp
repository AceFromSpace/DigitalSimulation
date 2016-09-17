#include "header.h"
#include <iostream>
//Interface 
using namespace std;
int main()
{
	

	std::cout << "choose mode : s-step mode ,n-normal." << std::endl;
	char step_or_normal;
	std::cin >> step_or_normal;
	bool chosed_mode=false;
	if (step_or_normal == 's')chosed_mode = true;



	cout << "Set number of lambda parameters " << endl;
	int number_of_simulations=-1;
	while(number_of_simulations<0)cin >> number_of_simulations;
	
	
	std::cout << "Set starting seed for seeds generator" << std::endl;
	int start=-1;
	while (start<0)std::cin >> start;
	


	cout << "Set starting lambda parameter" << endl;
	double lambda=-1;
	while (lambda<0)cin >> lambda;

	cout << "Choose number of simulation per lambda" << endl;
	int number_per_lambda=-1;
	while (number_per_lambda<0)cin >> number_per_lambda;
	
	cout << "Choose number of processes per simulation" << endl;
	int number_of_processes = -1;
	while (number_of_processes < 0)cin >> number_of_processes;
	
	statistics* stat = new statistics(number_of_simulations* number_per_lambda, number_per_lambda,number_of_processes);
	Generators* Generator= new Generators(number_of_simulations* number_per_lambda, start);


			for (int i = 0; i < number_of_simulations; i++)
			{
				for (int j = 0; j < number_per_lambda; j++)
				{
					
					Generator->go_to_the_next_simulation();
					Planner* x = new Planner(lambda, chosed_mode, Generator,stat, number_of_processes);
					int number = i * number_per_lambda + j;
					cout << "lambda: " << lambda << "  number of simulation " << number << endl;
					x->main_loop();
					stat->increase_current_number_of_simulation();
					delete x;
					cout << endl;
				}
				
				stat->average(i);
				stat->average_time_of_processing(i);//creates the tab of average processing for every simulation
				stat->average_time_for_lambda(i);
				cout << "Average usage of processor for 10 simulations: " << stat->return_average_usage(i) << endl;
				cout << "Average time of waiting in queues to devices for 10 simulations: " << stat->return_average_TODE(i) << endl;
				cout << "Average capacity of process for 10 simulations: " << stat->return_average_capacity(i) << endl;
				cout <<"Average time of waiting for 10 simulations: "<< stat->average_of_average_lambda() << endl;
				cout << "Average time of processing for 10 simulations: " << stat->average_of_average_processing(i) << endl;
				cout << "Average time of the longest processing: " << stat->return_average_max(i) << endl;
				stat->save_to_file_each_TOW();
				
				lambda = lambda + 0.001;
			}
	stat->save_to_file_all();
	stat->save_to_file_for_lamdba();
	stat->save_to_file_averages_only();
	stat->save_to_file_max();

	
	delete Generator;
	delete stat;
		getchar();
		getchar();
		return 0;
}