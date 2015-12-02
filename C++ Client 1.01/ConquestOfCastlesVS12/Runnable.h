#pragma once
#ifndef RUNNABLE_H
#define RUNNABLE_H

using namespace std;

namespace ConquestOfCastles {
	class Runnable {
	public:
		virtual void run(void) = 0;
	};
}

#endif