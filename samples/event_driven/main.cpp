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

#define SDL_MAIN_HANDLED
#include <SDL.h>

#ifdef __cplusplus
extern "C"
#endif
class testSurf : public beatoThread::btRefObj
{
public:
	testSurf(SDL_Renderer * renderRef) :
		beatoThread::btRefObj(),
		m_renderRef(renderRef),
		m_texMut()
	{
		m_tex = nullptr;
	}

	~testSurf(void)
	{
		clear();
	}

	void clear(void)
	{
		beatoThread::btMutexLock texLock(&m_texMut);
		if (m_tex)
		{
			SDL_DestroyTexture(m_tex);
			m_tex = nullptr;
		}
	}

	void load(const char * texDir)
	{
		clear();


		beatoThread::btMutexLock texLock(&m_texMut);
		SDL_Surface* TexSuf = SDL_LoadBMP(texDir);
		if (!TexSuf)
		{
			std::cout << "can't load surface " << texDir << " as texture " << SDL_GetError() << std::endl;
			return;
		}

		m_tex = SDL_CreateTextureFromSurface(m_renderRef, TexSuf);
		if (!m_tex)
		{
			std::cout << "can't create texture " << texDir << "as texture " << SDL_GetError() << std::endl;
			return;
		}
	}

	void renderTexture(void)
	{
		SDL_Rect texture_rect;
		texture_rect.x = 0;  //the x coordinate
		texture_rect.y = 0; // the y coordinate
		texture_rect.w = 256; //the width of the texture
		texture_rect.h = 256; //the height of the texture

		SDL_RenderCopy(m_renderRef, m_tex, NULL, &texture_rect);
	}

private:
	beatoThread::btMutex	m_texMut;
	SDL_Renderer *			m_renderRef;
	SDL_Texture*			m_tex;
};

class texLoadCall : 
	public beatoThread::btAsyncEventMethod,
	public beatoThread::btRefObj
{
public:
	texLoadCall(const char *texPath, beatoThread::btIntrusivePtr<testSurf> texRef) :
		loadPath(texPath),
		texHandle(texRef)
	{};
	
	~texLoadCall(void) 
	{};

	virtual void invoke(void)
	{
		texHandle->load(loadPath);
	}

private:
	beatoThread::btIntrusivePtr<testSurf> texHandle;
	const char* loadPath;
};



static void setUp(void)
{
}

static void setDown(void)
{
}

static void setLeft(void)
{
}

static void setRight(void)
{
}

SDL_Window *		window = nullptr;
SDL_Renderer *		windowRender = nullptr;
static void	startUpVideo(void)
{
	window = SDL_CreateWindow("Event Driven Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 256, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "can't create window" << std::endl;
		return;
	}

	windowRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (windowRender)
	{
		std::cout << "can't create window renderer" << std::endl;
		return;
	}
}

static void shutDownVideo(void)
{
	SDL_DestroyRenderer(windowRender);
	windowRender = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;
}

beatoThread::btIntrusivePtr<testSurf> base = nullptr;
beatoThread::btIntrusivePtr<testSurf> upSurf = nullptr;
beatoThread::btIntrusivePtr<testSurf> DnSurf = nullptr;
beatoThread::btIntrusivePtr<testSurf> LfSurf = nullptr;
beatoThread::btIntrusivePtr<testSurf> RgSurf = nullptr;

static void setImages(void)
{
	base = beatoThread::btIntrusivePtr<testSurf>(new testSurf(windowRender));
	upSurf = beatoThread::btIntrusivePtr<testSurf>(new testSurf(windowRender));
	DnSurf = beatoThread::btIntrusivePtr<testSurf>(new testSurf(windowRender));
	LfSurf = beatoThread::btIntrusivePtr<testSurf>(new testSurf(windowRender));
	RgSurf = beatoThread::btIntrusivePtr<testSurf>(new testSurf(windowRender));
}

int main(int argc, char *argv[])
{
	//clean sdl when quit
	atexit(SDL_Quit);

	SDL_Init(SDL_INIT_EVENTS || SDL_INIT_VIDEO);
	Uint32 err = SDL_WasInit(SDL_INIT_EVENTS);
	if (err != 0)
	{
		std::cout << "SDL_WasInit return " << err << "" << std::endl;
	}

	startUpVideo();

	//
	setImages();

	beatoThread::btDemultiplexThread worker = beatoThread::btDemultiplexThread();
	std::cout << "Starting Event Driven Test" << std::endl;
	std::cout << "hit \"escape\" to quit" << std::endl;
	//set to detach , so we don't need wait for thread when he ends
	worker.start(0, true);

	//star loading images in the woker thread
	worker.enqueueCapsule(new texLoadCall("assets/guide_base.bmp", base));
	worker.enqueueCapsule(new texLoadCall("assets/guide_up.bmp", upSurf));
	worker.enqueueCapsule(new texLoadCall("assets/guide_down.bmp", DnSurf));
	worker.enqueueCapsule(new texLoadCall("assets/guide_left.bmp", LfSurf));
	worker.enqueueCapsule(new texLoadCall("assets/guide_right.bmp", RgSurf));

	bool done = false;
	SDL_Event	evt;
	do
	{
		//clears the renderer
		SDL_RenderClear(windowRender);
		SDL_Rect cleanRec =  {  0, 0, 256, 256 };
		SDL_SetRenderDrawColor(windowRender, 255, 255, 255, 255);
		SDL_RenderFillRect(windowRender, &cleanRec);
		base->renderTexture();
#if 1
		//the main thread will wait until sdl handle a user event
		SDL_WaitEvent(&evt);
#else
		SDL_PollEvent(&evt);
#endif
		if (evt.type == SDL_QUIT)
			done = true;
		else if (evt.type == SDL_KEYDOWN)
		{
			SDL_KeyboardEvent keyEvt = evt.key;
			switch (keyEvt.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = true;
				break;
			case SDLK_UP:
				upSurf->renderTexture();
				break;
			case SDLK_DOWN:
				DnSurf->renderTexture();
				break;
			case SDLK_LEFT:
				LfSurf->renderTexture();
				break;
			case SDLK_RIGHT:
				RgSurf->renderTexture();
				break;
			default:
				continue;
			}
		}
		//updates the renderer
		SDL_RenderPresent(windowRender);
	} while (!done);
	std::cout << "exiting" << std::endl;

	//thread is a detached, we not need wait, only signal to end the loop
	worker.exit(false);

	shutDownVideo();

	//don't need on mingw debug 
	getchar();
	return 0;
}