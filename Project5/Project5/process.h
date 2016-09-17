#ifndef PROJECT5_PROCESS_H_
#define PROJECT5_PROCESS_H_
#include "event.h"
#include "processor.h"
#include "deviceIO.h"
#include "agenda.h"
#include <fstream>
#include <string>
#include <random>


//It is sequence of events. Cointain randomly generated times of next events , pointer to Event and variables which tell as about phase of process.
//It's a base class for class Task . 
class Event;
class Processor;
class DeviceIO;
class Agenda;
class Generators;



class Process
{
public:
	Process(Agenda* lis, Processor* proce, std::vector<DeviceIO*> &devfirst,double clock, Generators* gener, double lamb);
	~Process();
	
	//functions for counting time of using processor and time spending in queues to devices
	static int return_total_time_of_using_processor();
	static void reset_total_time_of_using_processor();
	static void stop_counting_time_of_processor();
	static void start_counting_time_of_processor();
	static double return_average_TODE();
	void collect_time_of_being_in_processor();
	void collect_TODE(double TODE);
	
	//main functions of Process
	void  execute();
	void activate(double time);
	void set_clock(double clk);

	//functions which are used to generate and manipulate time
	void randomTPG();//time to new process generation
	double get_TPG();
	void random_TPW();
	int get_TPW();
	void decrease_TPW();
	void random_TPIO();
	int get_TPIO();
	void random_TPO();
	int get_TPO();
	double get_TOL();
	double get_TOW();
	void random_TPD();
	int get_TPD();
	
	void random_deviceIO();//random device and set it as current_device
	Event* return_event();
	bool is_terminated();
	int return_phase();
	int return_number();
	int return_current_number();// return static value

	void set_mode(); //set step mode

private:
	static int current_number;
	static bool mode;
	static bool counting_time;//swiched on if starting phase is finish
	static int total_time_of_using_procesor; //total time in processor
	static int TODE_counter; //conuts times of being in queue to device
	static double sum_TODE; //sum of time of waiting to devices
	
	Event *my_event;
	Agenda *list;
	Generators* gen;
	int phase;
	bool terminated;
	double clock;
	int number;
	double lambda;

	double TOC;//time of create , clock value while process is creating
	double TOD;//time of death, clock value while process
	double TOL;//TOC-TOD
	double TOGTQ;//time when procces goes to the queue
	double TOLTQ;//time when procces leaves the queue
	double TOW;//summary time of waiting in queues
	double TPG; //next process generation time
	int TPW; //time which process will spend in processor
	int TPIO;// time of request to access to I/O device
	int TPO;//time which process will spend in I/O  device
	int TPD;//drawed number of device
	int sum_TPO_TPW; 
	double TODE;
	

	Processor* current_processor;
	std::vector<DeviceIO*> pointer_to_first_device;//vector of devices
	DeviceIO* current_deviceIO;
	
};

#endif