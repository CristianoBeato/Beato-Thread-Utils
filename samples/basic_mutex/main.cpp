/*
===========================================================================
btThread Source Code
Copyright (C) 2016-2018 Cristiano Beato dos Santos.
cristianobeato_dm@hotmail.com

This file is part of the btThread Source Code ("btThread a Beato SDL2 thread helper library").

btThread Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

btThread Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with btThread Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the btThread Source Code is also subject to certain additional terms.
You should have received a copy of these additional terms immediately following the terms and conditions
of the GNU General Public License which accompanied the btThread Source Code.
If not, please request a copy in writing from Cristiano B. S. at the email address below.

If you have questions concerning this license or the applicable additional terms,
you may contact in writing Cristiano "Beato", cristianobeato_dm@hotmail.com.
===========================================================================
*/

#include <beatoThread.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL_timer.h>

//disable this and thrad don't will wait before print
#define BT_DISBLE_PRINT_CTRL 0

//print Mutex
beatoThread::btMutex * printMtx = nullptr;

class Conter
{
public:
	Conter(unsigned int val) : countVal(val) 
	{
		countMutex = new beatoThread::btMutex;
	};

	~Conter(void) 
	{ 
		countVal = 0; 
		delete countMutex;
	};

	void decrase(void)
	{
		//auto initialize the mutex to protect the value 
		beatoThread::btMutexLock lock(countMutex);

		//
		if (countVal > 0)
			countVal--;
	};

	unsigned int getVal(void)
	{
		//protect from two thread get the number at same time
		beatoThread::btMutexLock lock(countMutex);
		return countVal;
	}

private:
	//the mutex
	beatoThread::btMutex	*countMutex;
	unsigned int			countVal;
};

class ThreadRun : public beatoThread::btThreadBase
{
public:
	ThreadRun(unsigned int thread, Conter *counter) : threadName(thread), count(counter) {};
	~ThreadRun(void) {};

	virtual int run(void)
	{
		if (!count)
			return -1;

		std::cout << "thread Test starting " << threadName << std::endl;
		
		while (true)
		{
			int curVal = count->getVal();
			if (curVal > 0)
				count->decrase();
			else
				break;

#if !BT_DISBLE_PRINT_CTRL
			printMtx->lock();
#endif //!BT_DISBLE_PRINT_CTRL
			std::cout << "Test Thread " << threadName << " count " << curVal << std::endl;
#if !BT_DISBLE_PRINT_CTRL
			printMtx->unlock();
#endif //!BT_DISBLE_PRINT_CTRL
			SDL_Delay(10);
		}

		return 0;
	}
private:
	unsigned int threadName;
	Conter *count;
};

int main()
{
	unsigned int  *valCalc = new unsigned int(600);

	std::cout << "Starting Basic Mutex Test" << std::endl;

#if !BT_DISBLE_PRINT_CTRL
	//mutex to control the print to console,
	//don't let the threads write outputs a the same time
	printMtx = new beatoThread::btMutex;
#endif

	//the counter 
	Conter valCount = Conter(100);

	//two workers threads, that procees the counter
	ThreadRun* Thread01 = new ThreadRun(1, &valCount);
	ThreadRun* Thread02 = new ThreadRun(2, &valCount);

	Uint32 thStart01 = SDL_GetTicks();
	Thread01->start();
	SDL_Delay(50);
	Uint32 thStart02 = SDL_GetTicks();
	Thread02->start();

	Thread01->wait();
	Uint32 thDelta01 = SDL_GetTicks() - thStart01;
	std::cout << "Thread 01 run " << thDelta01 << " milliseconds" << std::endl;

	Thread02->wait();
	Uint32 thDelta02 = SDL_GetTicks() - thStart02;
	std::cout << "Thread 02 run " << thDelta02 << " milliseconds" << std::endl;

	getchar();

	//clear thread handlers
	delete Thread02;
	delete Thread01;

#if !BT_DISBLE_PRINT_CTRL
	//clear mutexes
	delete printMtx;
#endif

	return 0;
}