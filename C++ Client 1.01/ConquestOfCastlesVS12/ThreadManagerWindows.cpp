#ifdef _WIN32

#include "ThreadManager.h"

#include <map>
#include <Windows.h>
#include <stdexcept>

using namespace ConquestOfCastles;
using namespace std;

namespace ConquestOfCastles {

	DWORD WINAPI ThreadFunction(LPVOID lpParam){
		auto runnable = static_cast<Runnable*>(lpParam);
		runnable->run();
		return 0;
	}

	map<Runnable*, HANDLE> ThreadManager::threads;

	int ThreadManager::submit(Runnable* runnable) 
	{

		DWORD identifier;
		HANDLE threadHandle;

		if ((threadHandle = CreateThread(
			nullptr,
			0,
			ThreadFunction,
			runnable,
			0,
			&identifier)) == nullptr)
			{
				throw ThreadCreationFailedException();
		}

		ThreadManager::threads[runnable] = threadHandle;

		return 0;
	}

	int ThreadManager::kill(Runnable* runnable) {
		if (ThreadManager::threads.find(runnable) == ThreadManager::threads.end())
			return 1;
		
		HANDLE threadHandle = ThreadManager::threads[runnable];

		if (TerminateThread(threadHandle, 1) &&
			CloseHandle(threadHandle)) {
			ThreadManager::threads.erase(runnable);
			return 0;
		}
		return 1;
	}

	void ThreadManager::sleep(int milliseconds) {
		// call to global Sleep in Windows.h
		::Sleep(milliseconds);
	}
}
#endif