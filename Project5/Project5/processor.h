#ifndef PROJECT5_PROCESSOR_H_
#define PROJECT5_PROCESSOR_H_
#include "process.h"
#include "generators.h"
#include <stdlib.h>
#include <queue>
//Represents procesor where go processes from queues.First queue is for  process which 
// are new in system . The secound one is for processes which come back from I/O device.
//Contains the bool variable busy , who tells about processor occupancy.

class Process;

class Processor
{
public:
	Processor(Generators* gener);
	~Processor();
	void get_busy();
	void release();
	bool is_it_busy();
	Process* return_first_queue1();
	int return_size_queue1();
	Process* return_first_queue2();
	int return_size_queue2();
	void add_to_queue1(Process* proc);
	void add_to_queue2(Process* proc);
	void remove_first_from_queue1();
	void remove_first_from_queue2();
	Process* choose_process();//choose process from queue and set him as a current
	Process* return_current();
	void set_current(Process* proc);
private:
	bool busy;
	Process *current;
	Generators* gen;
	std::queue<Process*> queue_to_processor1;
	std::queue<Process*> queue_to_processor2;
};
#endif