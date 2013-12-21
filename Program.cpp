#include "ThreadPoolExecutor.h"
#include "ExampleTask.h"
#include <iostream>

using namespace ThreadPool;

int main()
{
	ThreadPoolExecutor executor = ThreadPoolExecutor(4);

	for (int i = 0; i < 10; i++)
	{
		int random = std::rand() % 6;
		std::chrono::seconds timeout(random);
		executor.ScheduleTask([i, timeout](){
			std::cout << "no " << i << std::endl;
			std::this_thread::sleep_for(timeout);
		});
	}

	executor.Run();
	
	ExampleTask task;
	executor.ScheduleTask(task);
	std::this_thread::sleep_for(std::chrono::seconds(15));
		
	for (int i = 0; i < 10; i++)
	{
		int random = std::rand() % 6;
		std::chrono::seconds timeout(random);
		executor.ScheduleTask([i, timeout](){
			std::cout << "no " << i << std::endl;
			std::this_thread::sleep_for(timeout);
		});
	}

	return 0;
}
