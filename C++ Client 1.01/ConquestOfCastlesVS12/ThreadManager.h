#pragma once
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <iostream>
#include <stdexcept>
#include <map>

#include "Runnable.h"

using namespace std;

namespace ConquestOfCastles {

	class ThreadManager {
	private:
#ifdef _WIN32
		static map<Runnable*, void*> threads; //void* is handle
#endif
	public:
		static int submit(Runnable* runnable);
		static int kill(Runnable* runnable);
		static void sleep(int milliseconds);
	};

	class ThreadCreationFailedException : public runtime_error {
	public:
		ThreadCreationFailedException() : runtime_error("Thread creation failed.") {
			cerr << "Thread creation failed exception." << endl;
		};
	};

}

#endif