#include "statistics.h"



statistics::statistics(int number_of_sims, int number_of_simulation_per_l, int number_of_proc)
{
	number_of_simulation_per_lambda = number_of_simulation_per_l;
	total_number_of_simulations = number_of_sims;
	current_number_of_simulation = 0;
	number_of_processes = number_of_proc;
	
	tab_of_TOL = new double*[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_TOL[i] = new double[number_of_processes];
	for (int i = 0; i < number_of_sims; i++)
	{
		for (int j = 0; j < number_of_processes; j++)tab_of_TOL[i][j] = 0;
	}
	
	tab_of_time_of_processing = new double[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_time_of_processing[i] = 0;
	
	average_tab_of_time_of_processing =new double[number_of_sims / number_of_simulation_per_lambda];
	for (int i = 0; i < (number_of_sims / number_of_simulation_per_lambda); i++)average_tab_of_time_of_processing[i] = 0;

	tab_of_TOW = new double*[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_TOW[i] = new double[number_of_processes];
	for (int i = 0; i < number_of_sims; i++)
	{
		for (int j = 0; j < number_of_processes; j++)tab_of_TOW[i][j] = 0;
	}


	tab_of_time_per_lambda=new double[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_time_per_lambda[i] = 0;
	
	average_per_lambda = new double[(number_of_sims/ number_of_simulation_per_lambda)];
	for (int i = 0; i < (number_of_sims/ number_of_simulation_per_lambda); i++)average_per_lambda[i] = 0;
	
	average_tab_of_TOW = new double[number_of_processes];
	for (int i = 0; i < number_of_processes; i++)average_tab_of_TOW[i] = 0;

	tab_of_capacity = new double[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_capacity[i] = 0;

	average_tab_of_capacity = new double[number_of_sims / number_of_simulation_per_lambda];
	for (int i = 0; i < number_of_sims / number_of_simulation_per_lambda; i++)	average_tab_of_capacity[i] = 0;

	tab_of_processor_usage = new double[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_processor_usage[i] = 0;

	average_tab_of_usage = new double[number_of_sims / number_of_simulation_per_lambda];
	for (int i = 0; i < number_of_sims / number_of_simulation_per_lambda; i++)	average_tab_of_usage[i] = 0;

	tab_of_TODE = new double[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_TODE[i] = 0;

	average_tab_of_TODE = new double[number_of_sims / number_of_simulation_per_lambda];
	for (int i = 0; i < number_of_sims / number_of_simulation_per_lambda; i++)	average_tab_of_TODE[i] = 0;
	
	tab_of_max = new double[number_of_sims];
	for (int i = 0; i < number_of_sims; i++)tab_of_max[i] = 0;

	average_tab_of_max = new double[number_of_sims / number_of_simulation_per_lambda];
	for (int i = 0; i < number_of_sims / number_of_simulation_per_lambda; i++)	average_tab_of_max[i] = 0;


}


statistics::~statistics()
{
	for (int i = 0; i < total_number_of_simulations / number_of_simulation_per_lambda; i++)
	{
		delete[] tab_of_TOL[i];
	}
	delete[] tab_of_TOL;
	for (int i = 0; i < total_number_of_simulations / number_of_simulation_per_lambda; i++)
	{
		delete[] tab_of_TOW[i];
	}
	delete[] tab_of_TOW;


	delete[] tab_of_max;
	delete[] average_tab_of_max;
	delete[] average_tab_of_TOW;
	delete[] tab_of_time_per_lambda;
	delete[] tab_of_time_of_processing;
	delete[] average_tab_of_time_of_processing;
	delete[] average_per_lambda;
	delete[] tab_of_capacity;
	delete[] average_tab_of_capacity;
	delete[] tab_of_processor_usage;
	delete[] average_tab_of_usage;
	delete[] tab_of_TODE;
	delete[] average_tab_of_TODE;
}

void statistics::get_stats(Process * proc, int number)
{

	tab_of_TOW[current_number_of_simulation][number] = proc->get_TOW();
	tab_of_TOL[current_number_of_simulation][number] = proc->get_TOL();

}

void statistics::get_capacity_usage_TODE(double cap, double usa, double TODev)
{
	tab_of_capacity[current_number_of_simulation] = cap;
	tab_of_processor_usage[current_number_of_simulation] = usa;
	tab_of_TODE[current_number_of_simulation] = TODev;

}

void statistics::increase_current_number_of_simulation()
{
	current_number_of_simulation++;
}

void statistics::average(int k)
{
	double temp_sum;

	for (int i = 0; i < number_of_processes; i++)
	{
		temp_sum = 0;

		for (int j = number_of_simulation_per_lambda*k; j < number_of_simulation_per_lambda*(k+1); j++)
		{
			temp_sum = temp_sum + tab_of_TOW[j][i];
		}
		average_tab_of_TOW[i] = temp_sum / number_of_simulation_per_lambda;

	}
}
double statistics::average_of_average_lambda()
{
	double sum = 0;
	for (int i = 0; i < number_of_processes; i++)sum += average_tab_of_TOW[i];
	double avr = sum / number_of_processes;
	average_per_lambda[current_number_of_simulation / number_of_simulation_per_lambda-1] = avr;
	return avr;
}

double statistics::average_of_average_processing(int k)
{
	double sum = 0;
	
	for (int i = 0+k*number_of_simulation_per_lambda; i < number_of_simulation_per_lambda + number_of_simulation_per_lambda*k; i++)
	{
		for (int j = 0; j < number_of_processes; j++)
		{
			sum += tab_of_TOL[i][j];
		}
	}

	double avr = sum / (number_of_processes* number_of_simulation_per_lambda);
	average_tab_of_time_of_processing[current_number_of_simulation / number_of_simulation_per_lambda - 1] = avr;
	return avr;
}

void statistics::save_to_file_each_TOW()
{
	std::fstream file;
	file.open("average_times_of_waiting_lambda.txt", std::ios::app);
	file << "TOL" << " " << "TOW" << std::endl;
	for (int i = 0; i < number_of_processes; i++)
	{
		file << average_tab_of_TOW[i] << std::endl;
	}
	file << "NEXT SIMULATION" << std::endl;
	file.close();
}

double statistics::return_average_usage(int k)
{
	double sum = 0;
	for (int i = (0+ number_of_simulation_per_lambda*k); i < (number_of_simulation_per_lambda + number_of_simulation_per_lambda * k); i++)sum = sum + tab_of_processor_usage[i];
	double avr = sum / number_of_simulation_per_lambda;
	average_tab_of_usage[current_number_of_simulation / number_of_simulation_per_lambda - 1] = avr;
	return avr;
}

double statistics::return_average_TODE(int k)
{
	double sum = 0;
	for (int i = (0 + number_of_simulation_per_lambda * k); i < (number_of_simulation_per_lambda + number_of_simulation_per_lambda * k); i++)sum = sum + tab_of_TODE[i];
	double avr = static_cast<double>(sum) / number_of_simulation_per_lambda;
	average_tab_of_TODE[current_number_of_simulation / number_of_simulation_per_lambda - 1] = avr;
	return avr;
}

double statistics::return_average_max(int k)
{
	double sum = 0;
	for (int i = (0 + number_of_simulation_per_lambda * k); i < (number_of_simulation_per_lambda + number_of_simulation_per_lambda * k); i++)sum = sum + tab_of_max[i];
	double avr = sum / number_of_simulation_per_lambda;
	average_tab_of_max[current_number_of_simulation / number_of_simulation_per_lambda - 1] = avr;
	return avr;
}

double statistics::return_average_TOW_per_simulation()
{
	double sum = 0;
	for (int i = 0; i < number_of_processes; i++)sum = sum + tab_of_TOW[current_number_of_simulation][i];
	return sum / number_of_processes;
}

double statistics::return_average_TOL_per_simulation()
{
	double sum = 0;
	for (int i = 0; i < number_of_processes; i++)sum = sum + tab_of_TOL[current_number_of_simulation][i];
	return sum / number_of_processes;
}

double statistics::return_max_per_simulation()
{
	double max = 0;
	for (int i = 0; i < number_of_processes; i++)
	{
		if(tab_of_TOW[current_number_of_simulation][i]>max)max= tab_of_TOW[current_number_of_simulation][i];
	}
	return max;
}

double statistics::return_average_capacity(int k)
{
	double sum = 0;
	for (int i = (0 + number_of_simulation_per_lambda * k); i < (number_of_simulation_per_lambda + number_of_simulation_per_lambda * k); i++)sum = sum + tab_of_capacity[i];
	double avr = sum / number_of_simulation_per_lambda;
	average_tab_of_capacity[current_number_of_simulation / number_of_simulation_per_lambda - 1] = avr;
	return avr;
}

void statistics::save_to_file_for_lamdba()
{
	std::fstream file;
	file.open("average_time_per_sim.txt", std::ios::app);
	file << "TOL" << " " << "TOW" << std::endl;
	for (int i = 0; i < total_number_of_simulations/ number_of_simulation_per_lambda; i++)
	{
		for (int j = 0; j < number_of_simulation_per_lambda; j++)file << tab_of_time_per_lambda[i*number_of_simulation_per_lambda +j] << " ";
		file << average_per_lambda[i] << " "<<std::endl;

	}
	file << "NEXT SIMULATION" << std::endl;
	file.close();
}

void statistics::save_to_file_all()
{
	std::fstream file;
	file.open("all_params.txt", std::ios::app);
	file << "TOW" << " " << "TOL" <<" "<<"Max "<<" "<<"Capacity"<<" "<<"Usage%"<<" "<<"TODE"<<       std::endl;
	for (int i = 0; i < total_number_of_simulations/number_of_simulation_per_lambda; i++)
	{
		for (int j = 0; j < number_of_simulation_per_lambda; j++)
		{
			file << tab_of_time_per_lambda[i*number_of_simulation_per_lambda + j] << " ";
			file << tab_of_time_of_processing[i*number_of_simulation_per_lambda + j] << " ";
			file << tab_of_max[i*number_of_simulation_per_lambda + j] << " ";
			file << tab_of_capacity[i*number_of_simulation_per_lambda + j] << " ";
			file << tab_of_processor_usage[i*number_of_simulation_per_lambda + j] << " ";
			file << tab_of_TODE[i*number_of_simulation_per_lambda + j] << " ";
			file << endl;
		}
		file << average_per_lambda[i] << " ";
		file << average_tab_of_time_of_processing[i] << " ";
		file << average_tab_of_max[i] << " ";
		file << average_tab_of_capacity[i] << " ";
		file << average_tab_of_usage[i] << " ";
		file << average_tab_of_TODE[i] << " ";
		file << "NEXT Lambda" << std::endl;
	}

	file.close();


}

void statistics::save_to_file_averages_only()
{
	std::fstream file;
	file.open("only_average_params.txt", std::ios::app);
	file << "TOW" << " " << "TOL" << " " << "Max " << " " << "Capacity" << " " << "Usage%" << " " << "TODE" << std::endl;
	for (int i = 0; i < total_number_of_simulations / number_of_simulation_per_lambda; i++)
	{
	
		file << average_per_lambda[i] << " ";
		file << average_tab_of_time_of_processing[i] << " ";
		file << average_tab_of_max[i] << " ";
		file << average_tab_of_capacity[i] << " ";
		file << average_tab_of_usage[i] << " ";
		file << average_tab_of_TODE[i] << " ";
		file << endl;
	}

	file.close();


}

void statistics::save_to_file_max()
{
	std::fstream file;
	file.open("max_per_sim.txt", std::ios::app);
	file << "MAX" << std::endl;
	for (int i = 0; i < total_number_of_simulations / number_of_simulation_per_lambda; i++)
	{
		for (int j = 0; j < number_of_simulation_per_lambda; j++)file << tab_of_max[i*number_of_simulation_per_lambda + j] << " ";
		file << average_tab_of_max[i] << " " << std::endl;

	}
	file << "NEXT SIMULATION" << std::endl;
	file.close();
}

void statistics::average_time_for_lambda(int k)
{
	double temp_sum;
	double temp_max;
	for (int j = number_of_simulation_per_lambda*k; j < number_of_simulation_per_lambda*(k+1); j++)
	{
		temp_sum = 0;
		temp_max = 0;
		for (int i = 0; i < number_of_processes; i++)
		{
			if (tab_of_TOW[j][i]>temp_max)temp_max = tab_of_TOW[j][i];
			temp_sum = temp_sum + tab_of_TOW[j][i];
		}
		tab_of_time_per_lambda[j] = temp_sum / number_of_processes;
		tab_of_max[j] = temp_max;
	}
}

void statistics::average_time_of_processing(int k)
{
	double temp_sum;
	for (int j = number_of_simulation_per_lambda* k; j < number_of_simulation_per_lambda * (k + 1); j++)
	{
		temp_sum = 0;
		for (int i = 0; i < number_of_processes; i++)
		{
			temp_sum = temp_sum + tab_of_TOL[j][i];
		}
		tab_of_time_of_processing[j] = temp_sum / number_of_processes;
	}
}


