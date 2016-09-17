#ifndef PROJECT5_AGENDA_H_
#define PROJECT5_AGENDA_H_
#include "event.h"
#include <queue>


//It's a list of Events which allow manage simulation in time. Every Event represent process and his time 
class Event;
class Agenda
{
public:
	Agenda();
	~Agenda();
	
	Event* return_first();
	void add_to(Event* eve);
	void add_to_and_sort(Event* eve);//adds new event , and sort it by time
	void delete_event(Event* eve);
	void delete_first_event();
	void show_queue();
	int return_size();
	void delete_all();
	private:
	
	std::deque<Event*> list;
};

#endif