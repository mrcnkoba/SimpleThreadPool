#ifndef THREADPOOLEXECUTOR_H_
#define THREADPOOLEXECUTOR_H_

#include <functional>
#include <queue>
#include <thread>
#include <memory>
#include "Task.h"
#include <condition_variable>
#include "State.h"

namespace ThreadPool
{


	class ThreadPoolExecutor
	{
	public:
		ThreadPoolExecutor(int numWorkers);
		~ThreadPoolExecutor();
		void ScheduleTask(std::function<void()> task);
		void Run();
		void ShutDown();
		void CreateThread();
		void RemoveThread();

	private:
		state m_state;
		int m_numWorkers;
		bool m_finishingThread;
		std::vector<std::thread> m_workers;
		std::thread m_poolManager;
		std::mutex m_taskQueueMutex;
		std::mutex m_guard;
		std::queue<std::function<void()>> m_taskQueue;
		std::condition_variable m_notEmptyTaskQueue;
		void ManagePool();
		void RunWorker();
	};
}

#endif