#include <string>
#include <iostream>
#include <cmath>

#include <tiles/TileReader.hpp>

#include "SdlApplication.hpp"

#include "ImageLoader.hpp"

#include "Background.hpp"

using namespace Game;

const int BACK_SCROLL = 8;

class Application : public SdlApplication {
public:
    Application() :
	SdlApplication(),
        m_matrix(),
        m_background(NULL),
	m_imageLoader() {
    }

    void initResources(SDL_Surface* screen) {
        TileReader<TileType> reader;

        if (reader.load(boost::filesystem::path("matrix_small"), m_matrix)) {
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
    Matrix2D<TileType> m_matrix;
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
