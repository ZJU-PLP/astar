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

#include <string>
#include <iostream>
#include <cmath>

#include <image/ImageLoader.hpp>

#include <tiles/TileReader.hpp>

#include "SdlApplication.hpp"

#include "Background.hpp"

using namespace Game;

const int BACK_SCROLL = 32;

class Application : public SdlApplication {
public:
    Application() :
	SdlApplication(),
        m_matrix(),
        m_background(NULL),
	m_imageLoader() {
    }

    void initResources(SDL_Surface* screen) {
        TileReader<TileAndOverlay_s> reader;

        if (reader.load("matrix_big", m_matrix)) {
            m_background = new Background(m_imageLoader, &m_matrix);
        } else {
            throw Exception("Failed to read tilemap");
        }
    }

    void refresh(SDL_Surface* screen) {
        m_background->blit(screen);

        Uint8* keystate = SDL_GetKeyState(NULL);

        if (keystate[SDLK_LEFT] ) {
            m_background->scrollX(BACK_SCROLL);
        }
        if (keystate[SDLK_RIGHT] ) {
            m_background->scrollX(-BACK_SCROLL);
        }
        if (keystate[SDLK_UP] ) {
            m_background->scrollY(BACK_SCROLL);
        }
        if (keystate[SDLK_DOWN] ) {
            m_background->scrollY(-BACK_SCROLL);
        }

        int   mouseX = 0;
        int   mouseY = 0;
        Uint8 mbtns  = SDL_GetMouseState(&mouseX, &mouseY);

        if (mbtns & SDL_BUTTON(1)) {
            Point2D m = m_background->screenCoordsToMatrixIndex(Point2D(mouseY, mouseX));

            std::cout << "Clicked button 1 at i = " << m.y << " j = " << m.x << std::endl;
        }
    }

    ~Application() {
        delete m_background;
    }

private:
    Matrix2D<TileAndOverlay_s>   m_matrix;
    Background*        m_background;
    ImageLoader        m_imageLoader;
};

int main(int argc, char **argv) {
    srand(time(0));

    try {
	Application application;
	application.run();
    } catch (Exception& e) {
	Log::getInstance().print(
	    Log::Level_ERROR,
	    "[SdlApplication::run] Caught error: " + e.getMsg()
        );
    }

    return 0;
}
