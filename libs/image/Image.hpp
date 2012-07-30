#ifndef GAME_IMAGE_HPP
#define GAME_IMAGE_HPP

#include <SDL_image.h>

#include <common/Exception.hpp>
#include <common/Log.hpp>

namespace Game {

class Image {
public:
    Image(const std::string& path) :
        m_surface(NULL),
	m_path(path)
    {
	SDL_Surface* origImage = IMG_Load(path.c_str());

	if (origImage != NULL) {
	    m_surface = SDL_DisplayFormat(origImage);
	    SDL_FreeSurface(origImage);

	    if (m_surface == NULL) {
		throw Exception("Unable to convert " + path + " to display format");
	    }

            Uint32 key = SDL_MapRGB(m_surface->format, 255, 0, 255);
            SDL_SetColorKey(m_surface, SDL_RLEACCEL | SDL_SRCCOLORKEY, key);
	} else {
	    throw Exception("Unable to load image " + path);
	}

	Log::getInstance().print(
	    Log::Level_INFO,
	    "[Image::Image] Loaded " + path
        );
    }

    SDL_Surface* getSdlSurface() {
	return m_surface;
    }

    int getWidth() const {
	return m_surface->w;
    }

    int getHeight() const {
	return m_surface->h;
    }

    ~Image() {
	if (m_surface) {
	    SDL_FreeSurface(m_surface);

	    Log::getInstance().print(
		Log::Level_INFO,
		"[Image::Image] Freed " + m_path
	    );
	}
    }

private:
    SDL_Surface* m_surface;
    std::string  m_path;
};

} // Game

#endif // GAME_IMAGE_HPP
