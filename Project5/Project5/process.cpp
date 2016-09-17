#include "process.h"
#include "deviceIO.h"
#include "processor.h"
#include "agenda.h"
#include "generators.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>



using namespace std;


int Process::current_number = 0;
int Process::total_time_of_using_procesor = 0;
bool Process::mode = false; 
bool Process::counting_time = false;
int Process::TODE_counter = 0;
double Process::sum_TODE = 0;

Process::Process(Agenda* lis,Processor* proce, std::vector<DeviceIO*> &devfirst,double clk,Generators* gener, double lambd):phase(0), terminated(false),clock(clk),lambda(lambd)
{
	my_event = new Event(this);	
	current_processor = proce;
	pointer_to_first_device= devfirst;
	list = lis;
	TPW = 0;
	TOW = 0;
	TODE = 0;
	sum_TPO_TPW = 0;
	TOL = 0;
	gen = gener;
	number = current_number;
	current_number++;
}
Process::~Process()
{
	if (my_event != nullptr)
	delete my_event;
}
void Process::activate(double time)
{
	list->delete_event(my_event);
	my_event->set_event_time(static_cast<double>(clock + time));
	list->add_to_and_sort(my_event);
	
}
void Process::randomTPG()
{
	TPG = gen->TPG_Generator(lambda);	
}
double Process::get_TPG()
{
	return TPG;
}
void Process::random_TPW()
{
	
if (TPW == 0)TPW = gen->TPW_Generator();
	else
	{
		std::cout << "TPW has been chosen";
	}
}
void Process::execute()
{

	bool active = true;
	while (active)
	{
		switch (phase)
		{
		case 0:
		{
			TOC = clock;
			randomTPG();
			(new Process(list, current_processor, pointer_to_first_device, clock, gen, lambda))->activate(get_TPG());
			if (mode)cout << "TPG is:" << get_TPG() << endl;
			if (mode)cout << "Adding new process to queue1" << endl;
			current_processor->add_to_queue1(this);
			TOGTQ = clock;
			random_TPW();
			sum_TPO_TPW += TPW;
			if (mode)cout << "Drawing TPW" << endl;
			if (mode)cout << "TPW is:" << get_TPW() << endl;
			if (mode)cout << "Going to phase 1" << endl;
			if (mode)cout << endl;
			phase = 1;
			active = !current_processor->is_it_busy();
		}
		break;
		case 1:
		{
			if (mode)cout << "Choosing process" << endl;

			if (this != current_processor->return_current())
			{
				Process* temp = current_processor->choose_process();
				if (temp != this)
				{

					temp->activate(0);
					temp->set_clock(clock);
					active = false;
					break;
				}
			}
			if (this != current_processor->return_current())break;
			if (mode)cout << "Removing first process from queue1 " << endl;
			TOW = TOW + clock - TOGTQ;
			current_processor->remove_first_from_queue1();
			if (mode)cout << "Process is going to processor" << endl;
			current_processor->get_busy();
			random_TPIO();
			if (mode)cout << "Drawing time of request access to Device I/O" << endl;
			if (mode)cout << "TPIO is:" << get_TPIO() << endl;
			decrease_TPW();
			if (mode)cout << "Decreasing TPW" << endl;
			if (mode)cout << "New TPW is:" << get_TPW() << endl;
			if (get_TPIO() != 0)
			{
				if (mode)cout << "Going to the phase 2" << endl;
				if (mode)cout << endl;
				phase = 2;
				activate(get_TPIO());
				active = false;

			}
			else
			{
				if (mode)cout << "Going to the phase 6" << endl;
				if (mode)cout << endl;
				phase = 6;
				activate(get_TPW());
				active = false;
			}

		}
		break;
		case 2:
		{
			collect_time_of_being_in_processor();
			if (mode)cout << "Releasing processor" << endl;
			current_processor->release();
			Process* temp = current_processor->choose_process();
			if (temp != nullptr)
			{
				temp->set_clock(clock);
				temp->activate(0);
			}
			if (mode)cout << "Drawing device I/O " << endl;
			random_deviceIO();
			if (mode)cout << "Adding process to QUEUE to choosen device" << endl;
			current_deviceIO->add_to_queue(this);
			TODE = clock;
			if (mode)cout << "Going to the phase 3" << endl;
			if (mode)cout << endl;
			phase = 3;
			active = !current_deviceIO->is_it_busy();

		}
		break;
		case 3:
		{

			if (current_deviceIO->is_it_busy())cout << "Device is busy" << current_deviceIO->return_size() << endl;
			if (current_deviceIO->return_first() != this)
			{
				if (mode)	cout << "Choosing first process from queue to device" << endl;
				if (current_deviceIO->return_first() != nullptr)
				{
					current_deviceIO->return_first()->set_clock(clock);
					current_deviceIO->return_first()->activate(0);
				}
				else
				{
					if (mode)	cout << "Error , not this and not first device?" << endl;
				}
				active = false;
				break;
			}
	
			if (mode)cout << "Removing process from queue to device and device is getting busy" << endl;
			current_deviceIO->remove_first_from_queue();
			current_deviceIO->get_busy();
			random_TPO();
			sum_TPO_TPW += TPO;
			activate(get_TPO());
			TODE = clock - TODE;
			collect_TODE(TODE);

			if (mode)cout << "Drawed TPO is:" << TPO << endl;
			if (mode)cout << "Going to the phase 4:" << endl;
			if (mode)cout << endl;
			phase = 4;
			active = false;
		}
			break;
		case 4:
		{
			if (mode)cout << "Releasing device I/O" << endl;
			current_deviceIO->release();
			if (current_deviceIO->return_first() != nullptr)
			{
				if (mode)cout << "Adding next process to device I/O" << endl;
				current_deviceIO->return_first()->set_clock(clock);
				current_deviceIO->return_first()->activate(0);
				if (mode)cout << "Added next process to device I/O" << endl;

			}
			if (mode)cout << "Adding process to queue2" << endl;
			current_processor->add_to_queue2(this);
			TOGTQ = clock;
			if (mode)cout << "Going to phase 5" << endl;
			if (mode)cout << endl;
			phase = 5;
			active = !current_processor->is_it_busy();
		}
		break;
		case 5:
		{
			if (this != current_processor->return_current())
			{
				Process* temp = current_processor->choose_process();
				if (temp != this&&temp != nullptr)
				{
					if (mode)cout << "Adding new process to processor from queue1" << endl;
					temp->set_clock(clock);
					temp->activate(0);
					active = false;
					break;
				}
			}
			if (this != current_processor->return_current())break;
			if (mode)cout << "Process is going to the processor next time" << endl;
			current_processor->remove_first_from_queue2();
			TOW = TOW + clock - TOGTQ;
			current_processor->get_busy();
			if (mode)cout << "Drawing TPIO" << endl;
			random_TPIO();
			if (mode)cout << "TPIO is:" << get_TPIO() << endl;
			decrease_TPW();
			if (mode)cout << "Decreasing TPW" << endl;
			if (mode)cout << "New TPW is: " << get_TPW() << endl;
			if (get_TPIO() == 0)
			{
				if (mode)cout << "Next process activation in " << get_TPW() << endl;
				if (mode)cout << "Going to the phase 6" << endl;
				if (mode)cout << endl;
				activate(get_TPW());
				phase = 6;
				active = false;
			}
			else
			{
				if (mode)cout << "Going to the phase 2" << endl;
				if (mode)cout << endl;
				phase = 2;
				activate(get_TPIO());
				active = false;
			}
		}
		break;
		case 6:
		{

			if (mode)cout << "Releasing processor" << endl;
			if (mode)cout << "Deleting process from system" << endl;
			TOD = clock;
			current_processor->release();
			collect_time_of_being_in_processor();
			Process* temp = current_processor->choose_process();
			if (temp != nullptr)
			{
				if (mode)cout << "Adding next process to processor" << endl;
				temp->set_clock(clock);
				temp->activate(0);
			}

			active = false;
			terminated = true;
		}
		break;
		}
	}
 }
	

int Process::get_TPW()
{
	return TPW;
}
void Process::decrease_TPW()
{
	TPW = TPW - TPIO;
	if (TPW < 0)TPW = 0;
}
void Process::random_TPIO()
{
	TPIO = gen->TPIO_Generator(get_TPW());
}
int Process::get_TPIO()
{
	return TPIO;
}
void Process::random_TPO()
{
	TPO = gen->TPO_Generator();
}
int Process::get_TPO()
{
	return TPO;
}
double Process::get_TOL()
{
	TOL = TOD - TOC;
	return TOL;
}
double Process::get_TOW()
{
	return TOW;
}
void Process::random_TPD()
{
	TPD = gen->TPD_Generator();
}
int Process::get_TPD()
{
	return TPD;
}
void Process::set_clock(double clk)
{
	clock = clk;
}
void Process::random_deviceIO()
{
	random_TPD();
	if (mode)cout << "Choosen device is: "<<get_TPD() << endl;
	current_deviceIO = pointer_to_first_device[get_TPD()];
}

Event * Process::return_event()
{
	return my_event;
}
bool Process::is_terminated()
{
	return terminated;
}
int Process::return_number()
{
	return number;
}
int Process::return_current_number()
{
	return current_number;
}
void Process::collect_time_of_being_in_processor()
{
	if (counting_time)
	{
		if (TPIO != 0)total_time_of_using_procesor = total_time_of_using_procesor + TPIO;
		else total_time_of_using_procesor = total_time_of_using_procesor + TPW;
	}

}
void Process::collect_TODE(double TODE)
{
	if (counting_time)
	{
		if (TODE_counter < 70000)
		{
			sum_TODE = sum_TODE + TODE;
			TODE_counter++;
		}
	}
}
int Process::return_total_time_of_using_processor()
{
	return total_time_of_using_procesor;
}
void Process::reset_total_time_of_using_processor()
{
	total_time_of_using_procesor= 0;
}
void Process::stop_counting_time_of_processor()
{
	counting_time = false;
}
void Process::start_counting_time_of_processor()
{
	counting_time = true;
}
double Process::return_average_TODE()
{
	double output = sum_TODE / 70000;
	sum_TODE = 0;
	TODE_counter = 0;
	return output;
}
void Process::set_mode()
{
	mode = true;
}
int Process::return_phase()
{
	return phase;
}
