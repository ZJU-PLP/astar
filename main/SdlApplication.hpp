// Copyright (C) 2012 by Kristian Rumberg <kristianrumberg@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef GAME_SDLAPPLICATION_HPP
#define GAME_SDLAPPLICATION_HPP

#include <SDL.h>

#include <common/Exception.hpp>
#include <common/Log.hpp>

namespace {
    const int SCREEN_WIDTH  = 800;
    const int SCREEN_HEIGHT = 600;
}

namespace Game {

class SdlApplication {
public:
    SdlApplication() :
        m_gameover(false)
    {
    }

    void run() {
	initSdl();
	initResources(SDL_GetVideoSurface());

	enterMainloop();
    }

    ~SdlApplication() {
	SDL_Quit();
    }
private:

    void initSdl() {
	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	SDL_WM_SetCaption("Best Game Ever", "Best Game Ever");

	/* create window */
	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
     }

    virtual void initResources(SDL_Surface* screen) = 0;

    void enterMainloop() {
	SDL_Surface* screen = SDL_GetVideoSurface();

        int ndraws = 0;

        /* message pump */
        while (!m_gameover) {
	    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	    handleEvents();

	    refresh(screen);

	    /* update the screen */
	    SDL_Flip(screen);

            ++ndraws;
	}

        std::cout << "ndraws = " << ndraws << std::endl;
    }

    virtual void refresh(SDL_Surface* screen) = 0;

    void handleEvents() {
	SDL_Event eve;
	/* look for an event */
	if (SDL_PollEvent(&eve)) {
	    /* an event was found */
	    switch (eve.type) {
		/* close button clicked */
  	        case SDL_QUIT:
		    m_gameover = true;
		    break;

		    /* handle the keyboard */
		    case SDL_KEYDOWN:
			switch (eve.key.keysym.sym) {
  			    case SDLK_ESCAPE:
			    case SDLK_q:
    	         	    m_gameover = true;
			    break;
			}

  		    default:
			break;
		}
	}
    }

    int m_gameover;
};

} // Game

#endif // GAME_SDLAPPLICATION_HPP
