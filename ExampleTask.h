#ifndef EXAMPLETASK_H_
#define EXAMPLETASK_H_

#include "Task.h"

namespace ThreadPool{
	class ExampleTask :
		public Task
	{
	public:
		ExampleTask();
		~ExampleTask();
		void operator()() override;
	};
}

#endif