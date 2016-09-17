#include "agenda.h"
#include<iostream>

using namespace std;

Agenda::Agenda()
{

}
Agenda::~Agenda()
{
}
Event* Agenda::return_first()
{
	if(!list.empty())return list.front();
	return nullptr;
}
void  Agenda::add_to(Event* eve)
{
	
	list.push_back(eve);
	
}
void Agenda::add_to_and_sort(Event * eve)
{
	
	if(list.empty())list.push_back(eve);
	else
	{
		
		int i ;
		Event* temp;
		
		for ( i = 0; i < list.size(); i++)
		{
			temp = list[i];
			if (temp->get_event_time() > eve->get_event_time())break;
			
		}

		list.insert(list.begin()+i, eve); 


	}

}
void Agenda::delete_event(Event * eve)
{
	int i = 0;
	bool flag = false;
	for (i = 0; i < list.size(); i++)
	{
		if (list[i] == eve)
		{
			flag = true;
			break;
			
		}
	}
	if(flag)list.erase(list.begin() + i);
	
}
void Agenda::delete_first_event()
{
	if(!list.empty())list.erase(list.begin());
}
void Agenda::show_queue()
{
	for (int i = 0; i < list.size(); i++)std::cout << list[i]->get_event_time() << " " << list[i]->return_proc()->return_phase() << " "<< list[i]->return_proc()->return_number() <<std::endl;
}
int Agenda::return_size()
{
	return list.size();
}
void Agenda::delete_all()
{
	for (int i = 0; i < list.size(); i++)
	{
		Event* temp = list.front();
		list.pop_front();
		delete temp;
	}
}
