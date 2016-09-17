#include "generators.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

Generators::Generators(int number_of_sim,int start_point)
{
	
	number_of_simulations = number_of_sim;
	current_number_of_sim = -1;
	TPW_hist = new int[51];
	for (int i = 0; i < 51; i++)TPW_hist[i] = 0;
	TPO_hist = new int[11];
	for (int i = 0; i < 11; i++)TPO_hist[i] = 0;
	TPIO_hist = new int[50];
	for (int i = 0; i < 50; i++)TPIO_hist[i] = 0;
	TPD_hist = new int[10];
	for (int i = 0; i < 10; i++)TPD_hist[i] = 0;
	TPG_hist = new int[1000];
	for (int i = 0; i < 1000; i++)TPG_hist[i] = 0;
	TPP_hist = new int[10];
	for (int i = 0; i < 10; i++)TPP_hist[i] = 0;

	SEEDS = new int*[number_of_sim];
	for (int i = 0; i < number_of_sim; i++)SEEDS[i] = new int[6];
	seeds_Generator(start_point);
	
}
Generators::~Generators()
{
	delete[] TPW_hist;
	delete[] TPO_hist;
	delete[] TPIO_hist;
	delete[] TPD_hist;
	delete[] TPG_hist;
	delete[] TPP_hist;

	
	for (int i = 0; i < number_of_simulations; i++)
	{
		delete[] SEEDS[i];
	}
	delete[] SEEDS;

	
}
int Generators::TPW_Generator()
{
	int h = TPW / 127773;
	TPW = 16807 * (TPW - 127773 * h) - 2836 * h;
	if (TPW < 0)TPW = TPW + 2147483647;
	int output_TPW = TPW % 50 + 1;
	TPW_hist[output_TPW]++;
	return output_TPW;
}
int Generators::TPO_Generator()
{

	int h = TPO / 127773;
	TPO = 16807 * (TPO - 127773 * h) - 2836 * h;
	if (TPO < 0)TPO = TPO + 2147483647;
	int output_TPO = TPO % 10 + 1;
	TPO_hist[output_TPO]++;
	return output_TPO;
	
}
int Generators::TPIO_Generator(int new_TPW)
{
	
	int h = TPIO / 127773;
	TPIO = 16807 * (TPIO - 127773 * h) - 2836 * h;
	if (TPIO < 0)TPIO = TPIO + 2147483647;
	int output_TPIO = TPIO % new_TPW;
	TPIO_hist[output_TPIO]++;
	return output_TPIO;
	
}
int Generators::TPD_Generator()
{
	
	int h = TPD / 127773;
	TPD = 16807 * (TPD - 127773 * h) - 2836 * h;
	if (TPD < 0)TPD = TPD + 2147483647;
	int output_TPD = TPD % 10 ;
	TPD_hist[output_TPD]++;
	return output_TPD;
}
int Generators::TPP_Generator()
{
	int h = TPP / 127773;
	TPP = 16807 * (TPP - 127773 * h) - 2836 * h;
	if (TPP < 0)TPP = TPP + 2147483647;
	int output_TPP = TPP % 10;
	TPP_hist[output_TPP]++;
	return output_TPP;
}
double Generators::TPG_Generator(double lambda)
{
	
	int h = TPG_uni / 127773;
	TPG_uni = 16807 * (TPG_uni - 127773 * h) - 2836 * h;
	if (TPG_uni < 0)TPG_uni = TPG_uni + 2147483647;
	double TPG_temp= static_cast<double>(TPG_uni)/2147483647;
	double TPG = -log(TPG_temp) / lambda;
	double output_TPG = TPG;
	if (output_TPG > 999)output_TPG = 999;
	TPG_hist[static_cast<int>(output_TPG)]++;
	return TPG;
}
void Generators::seeds_Generator(int start_point)
{

	int h = 0;
	int temp_seed = start_point;

	for (int j = 0; j < number_of_simulations; j++)
	{
		int k = 0;
			for (int i = 1; i <= (6*250000); i++)
			{
				h = temp_seed / 127773;
				temp_seed = 16807 * (temp_seed - 127773 * h) - 2836 * h;
				if (temp_seed < 0)temp_seed = temp_seed + 2147483647;
				if ((i % 250000 == 0) && (k <6 ))
				{
					SEEDS[j][k] = temp_seed;
					k++;
				}
			}

	}
	TPW = SEEDS[0][0];
	TPO = SEEDS[0][1];
	TPIO = SEEDS[0][2];
	TPD = SEEDS[0][3];
	TPG_uni = SEEDS[0][4];
	TPP = SEEDS[0][5];
}

void Generators::save_stats_to_file()
{
	std::fstream file;
	file.open("generators_histograms.txt", std::ios::app);
	
	file << "TPW: TPO: TPIO: TPD: TPG";
	file << std::endl;
	for (int i = 0; i < 10;i++)file << TPW_hist[i] <<" "<< TPO_hist[i] << " " << TPIO_hist[i] << " " << TPD_hist[i] << " " << TPG_hist[i] << " " << std::endl;
							   file << TPW_hist[10] << " " << TPO_hist[10] << " " << TPIO_hist[10] << " " << "x" << " " << TPG_hist[10] << " " << std::endl;
	for (int i = 11; i < 50; i++)file << TPW_hist[i] << " " << "x" << " " << TPIO_hist[i] << " " << "x" << " " << TPG_hist[i] << " " << std::endl;
									file << TPW_hist[51] << " " << "x" << " " << "x" << " " << "x" << " " << TPG_hist[51] << " " << std::endl;
	for (int i = 51; i < 1000; i++)file <<  "x"  << " " << "x" << " " <<  "x"  << " " << "x" << " " << TPG_hist[i] << " " << std::endl;
	file.close();
}

void Generators::go_to_the_next_simulation()
{
	current_number_of_sim++;
	TPW = SEEDS[current_number_of_sim][0];
	TPO = SEEDS[current_number_of_sim][1];
	TPIO = SEEDS[current_number_of_sim][2];
	TPD = SEEDS[current_number_of_sim][3];
	TPG_uni = SEEDS[current_number_of_sim][4];
	TPP = SEEDS[current_number_of_sim][5];
}



