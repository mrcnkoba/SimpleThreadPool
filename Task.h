#ifndef TASK_H_
#define TASK_H_

#include <mutex>
namespace ThreadPool
{
	class Task
	{
	public:
		Task();
		virtual ~Task();
		virtual void operator()() = 0;
	};
}

#endif