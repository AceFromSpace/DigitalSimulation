#ifndef PROJECT5_EVENT_H_
#define PROJECT5_EVENT_H_
#include "process.h"
// Represent event which is the message about process . Every Event contains pointer to his process and time of his next appear in system.
class Process;
class Event
{
public:
	Event(Process *ptr);
	~Event();
	double get_event_time();
	void set_event_time(double ev_time);
	Process* return_proc();
private:
	double event_time;
	Process* proc;
};
#endif

