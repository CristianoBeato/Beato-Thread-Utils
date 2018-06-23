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

class ThreadRun : public beatoThread::btThreadBase
{
public:
	ThreadRun(unsigned int thread, int times) : threadName(thread), count(times) {};
	~ThreadRun(void) {};

	virtual int run(void)
	{
		std::cout << "thread Test starting " << threadName << std::endl;
		SDL_Delay(100);
		
		while (count > 0)
		{
			std::cout << "Test Thread " << threadName << " count " << count << std::endl;
			count--;
		}

		return count;
	}
private:
	unsigned int threadName;
	int count;
};

int main()
{
	std::cout << "Starting Basic Thread Test" << std::endl;

	ThreadRun* Thread01 = new ThreadRun(1, 400);
	ThreadRun* Thread02 = new ThreadRun(2, 200);

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
	return 0;
}