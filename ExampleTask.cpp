#include "ExampleTask.h"
#include <iostream>

namespace ThreadPool
{
	ExampleTask::ExampleTask()
	{
	}


	ExampleTask::~ExampleTask()
	{
	}

	void ExampleTask::operator()()
	{
		std::cout << "hello world from example task" << std::endl;
	}
}
