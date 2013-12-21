#pragma once

#include <thread>

class Worker
{
public:
	Worker();
	virtual ~Worker();
	
protected:
	std::thread _thread;
	
};

