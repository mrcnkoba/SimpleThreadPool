#include "ThreadPoolExecutor.h"
#include <algorithm>
#include <iostream>

namespace ThreadPool
{
	ThreadPoolExecutor::ThreadPoolExecutor(int maxWorkers)
	{
		this->maxWorkers = maxWorkers;
	}

	ThreadPoolExecutor::~ThreadPoolExecutor()
	{
		this->poolManager.join();
	}

	void ThreadPoolExecutor::ScheduleTask(std::function<void()> task)
	{
		std::unique_lock<std::mutex> lock(taskQueueMutex);
		bool wasEmpty = this->taskQueue.empty();
		this->taskQueue.push(task);
		if (wasEmpty)
		{
			this->notEmptyTaskQueue.notify_one();
		}
		
		lock.unlock();
	}

	void ThreadPoolExecutor::Run()
	{
		this->poolManager = std::thread(&ThreadPoolExecutor::ManagePool, this);
	}

	void ThreadPoolExecutor::ManagePool()
	{
		for (int i = 0; i < this->maxWorkers; i++)
		{
			this->workers.push_back(std::thread(&ThreadPoolExecutor::Worker, this));
		}

		for (auto &thread : this->workers)
		{
			thread.join();
		}
	}

	void ThreadPoolExecutor::Worker()
	{
#ifdef _DEBUG
		std::cout << "Hello from thread: " << std::this_thread::get_id() << std::endl;
#endif
		while (1)
		{
			std::unique_lock<std::mutex> lock(taskQueueMutex);
			if (this->taskQueue.empty())
			{
				this->notEmptyTaskQueue.wait(lock);
			}
						
			auto task = this->taskQueue.front();
			this->taskQueue.pop();
			lock.unlock();
			task();
		}
	}
}
