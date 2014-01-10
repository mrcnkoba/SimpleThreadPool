#include "ThreadPoolExecutor.h"
#include "ExampleTask.h"
#include <iostream>

using namespace ThreadPool;

int main()
{
	ThreadPoolExecutor executor = ThreadPoolExecutor(4);

	for (int i = 0; i < 2; i++)
	{
		int random = std::rand() % 6;
		std::chrono::seconds timeout(random);
		executor.ScheduleTask([i, timeout](){
			std::cout << "no " << i << std::endl;
			std::this_thread::sleep_for(timeout);
		});
	}

	executor.Run();
	executor.RemoveThread();
	ExampleTask task;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	executor.ScheduleTask(task);
	executor.CreateThread();
	
		
	for (int i = 0; i < 2; i++)
	{
		int random = std::rand() % 6;
		std::chrono::seconds timeout(random);
		executor.ScheduleTask([i, timeout](){
			std::cout << "no " << i << std::endl;
			std::this_thread::sleep_for(timeout);
		});
	}

	executor.ShutDown();
	return 0;
}
