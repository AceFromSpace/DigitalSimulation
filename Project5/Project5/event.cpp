#include "event.h"
#include <iostream>



Event::Event(Process* ptr) :event_time(-1.0), proc(ptr)
{

}

Event::~Event()
{
//destructor of proc delete this
}
double Event::get_event_time()
{
	return event_time;
}

void Event::set_event_time(double ev_time)
{
	event_time = ev_time;
	
}
Process* Event::return_proc()
{
	return proc;

}