#include "processor.h"
#include <iostream>



Processor::Processor(Generators* gener) :busy(false)
{
	gen = gener;
}

Processor::~Processor()
{
	
	std::queue<Process*> empty1;
	std::queue<Process*> empty2;
	std::swap(queue_to_processor1, empty1);
	std::swap(queue_to_processor2, empty2);
	
}
void Processor::get_busy()
{
	busy = true;

}
void Processor::release()
{
	busy = false;
}
bool Processor::is_it_busy()
{
	return busy;
}

Process * Processor::return_first_queue1()
{
	if(!queue_to_processor1.empty())return queue_to_processor1.front();
	return nullptr;
}

int Processor::return_size_queue1()
{
	return queue_to_processor1.size();
}

Process * Processor::return_first_queue2()
{
	if (!queue_to_processor2.empty())return queue_to_processor2.front();
	return nullptr;
}

int Processor::return_size_queue2()
{
	return queue_to_processor2.size();
}

void Processor::add_to_queue1(Process * proc)
{
	queue_to_processor1.push(proc);
}
void Processor::add_to_queue2(Process * proc)
{
	 queue_to_processor2.push(proc);
}

void Processor::remove_first_from_queue1()
{
	if (!queue_to_processor1.empty()) queue_to_processor1.pop();
	else std::cerr << "queue1 is empty!" << std::endl;
}
void Processor::remove_first_from_queue2()
{
	if (!queue_to_processor2.empty()) queue_to_processor2.pop();
	else std::cerr << "queue2 is empty!" << std::endl;
}

Process* Processor::choose_process()
{
	if (queue_to_processor2.empty())
	{
		set_current(return_first_queue1());
		return return_first_queue1();
	}
	else if (queue_to_processor1.empty())
	{
		set_current(return_first_queue2());
		return return_first_queue2();
	}
	else if (queue_to_processor1.empty() && queue_to_processor2.empty())
	{
		set_current(nullptr);
		return nullptr;
	}
	else 
	{
		int x = gen->TPP_Generator();
		if (x < 2)
		{
			set_current(return_first_queue1());
			return return_first_queue1();
		}
		else
		{
			set_current(return_first_queue2());
			return return_first_queue2();
		}
	}
	
}


Process * Processor::return_current()
{
	return current;
}

void Processor::set_current(Process* proc)
{
	current = proc;
}
