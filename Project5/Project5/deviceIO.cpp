#include "deviceIO.h"
#include <iostream>



DeviceIO::DeviceIO():busy(false)
{
	current = nullptr;
}

DeviceIO::~DeviceIO()
{
	delete current;
	std::queue<Process*> empty1;
	std::swap(queue_to_device, empty1);
}
void DeviceIO::get_busy()
{
	busy=true;
}
void DeviceIO::release()
{
	busy = false;
}
bool  DeviceIO::is_it_busy()
{
	return busy;
}

Process * DeviceIO::return_first()
{
	if (!queue_to_device.empty())return queue_to_device.front();
	else 
	{
		//std::cout << "queue to device is empty!" << std::endl;
		return nullptr;
	}
}

void DeviceIO::add_to_queue(Process * proc)
{
	queue_to_device.push(proc);
}

void DeviceIO::remove_first_from_queue()
{
	if (!queue_to_device.empty()) queue_to_device.pop();
	else std::cerr << "queue to device is empty!" << std::endl;
	
}

void DeviceIO::show_queue()
{
	while(queue_to_device.empty()==false)
	{
		std::cout << queue_to_device.front()->get_TPW() << std::endl;
		queue_to_device.pop();
	}
}

int DeviceIO::return_size()
{
	return queue_to_device.size();
}
