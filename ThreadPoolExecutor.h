#ifndef THREADPOOLEXECUTOR_H_
#define THREADPOOLEXECUTOR_H_

#include <functional>
#include <queue>
#include <thread>
#include <memory>
#include "Task.h"
#include <condition_variable>

namespace ThreadPool
{
	class ThreadPoolExecutor
	{
	public:
		ThreadPoolExecutor(int maxWorkers);
		~ThreadPoolExecutor();
		void ScheduleTask(std::function<void()> task);
		void Run();

	private:
		int maxWorkers;
		std::vector<std::thread> workers;
		std::thread poolManager;
		std::queue<std::function<void()>> taskQueue;
		std::condition_variable notEmptyTaskQueue;
		void ManagePool();
		std::mutex taskQueueMutex;
		void Worker();
	};
}

#endif