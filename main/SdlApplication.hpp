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
	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
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
	    SDL_UpdateRect(screen, 0, 0, 0, 0);

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
