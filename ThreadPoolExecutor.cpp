#include "ThreadPoolExecutor.h"
#include <algorithm>
#include <iostream>

namespace ThreadPool
{
	ThreadPoolExecutor::ThreadPoolExecutor(int numWorkers) : m_numWorkers(numWorkers), m_state(state::RUNNING)
	{
	}

	ThreadPoolExecutor::~ThreadPoolExecutor()
	{
		m_poolManager.join();
	}

	void ThreadPoolExecutor::ScheduleTask(std::function<void()> task)
	{
		std::unique_lock<std::mutex> lock(m_taskQueueMutex);
		bool wasEmpty = m_taskQueue.empty();
		m_taskQueue.push(task);
		if (wasEmpty)
		{
			m_notEmptyTaskQueue.notify_one();
		}
	}

	void ThreadPoolExecutor::Run()
	{
		m_poolManager = std::thread(&ThreadPoolExecutor::ManagePool, this);
	}

	void ThreadPoolExecutor::ManagePool()
	{
		for (int i = 0; i < m_numWorkers; i++)
		{
			m_workers.push_back(std::thread(&ThreadPoolExecutor::RunWorker, this));
		}

		for (auto &thread : m_workers)
		{
			thread.join();
		}
	}

	void ThreadPoolExecutor::RunWorker()
	{
#ifdef _DEBUG
		std::cout << "Hello from thread: " << std::this_thread::get_id() << std::endl;
#endif
		while (m_state == state::RUNNING)
		{
			std::unique_lock<std::mutex> lock(m_taskQueueMutex);
			if (m_taskQueue.empty())
			{
				m_notEmptyTaskQueue.wait(lock);
				if (m_state == state::SHUTDOWN)
					break;
			}
						
			auto task = m_taskQueue.front();
			m_taskQueue.pop();
			lock.unlock();
			task();
		}
#ifdef _DEBUG
		std::cout << "Thread: " << std::this_thread::get_id() << " finished" << std::endl;
#endif
	}

	void ThreadPoolExecutor::ShutDown()
	{
		m_state = state::SHUTDOWN;
		m_notEmptyTaskQueue.notify_all();
	}

	void ThreadPoolExecutor::CreateThread()
	{
		m_workers.push_back(std::thread(&ThreadPoolExecutor::RunWorker, this));
	}

	void ThreadPoolExecutor::RemoveThread()
	{

	}
}
