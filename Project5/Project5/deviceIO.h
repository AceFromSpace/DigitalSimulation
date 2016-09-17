#ifndef PROJECT5_DEVICEIO_H_
#define PROJECT5_DEVICEIO_H_
#include "process.h"
#include <queue>
//Represents I/O device where go processes from queue.Contains the bool variable busy , who tells about processor occupancy.
class Process;
class DeviceIO
{
public:
	DeviceIO();
	~DeviceIO();
	void get_busy();
	void release();
	bool is_it_busy();
	Process* return_first();
	void add_to_queue(Process* proc);	
	void remove_first_from_queue();
	void show_queue();
	int return_size();
private:
	bool busy;
	std::queue<Process*> queue_to_device;
	Process *current;

};
#endif
