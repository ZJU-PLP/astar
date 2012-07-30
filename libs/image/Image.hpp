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
	    m_surface = SDL_DisplayFormatAlpha(origImage);
	    SDL_FreeSurface(origImage);

	    if (m_surface == NULL) {
		throw Exception("Unable to convert " + path + " to display format");
	    }

            //Uint32 key = SDL_MapRGB(m_surface->format, 255, 0, 255);
            //SDL_SetColorKey(m_surface, SDL_RLEACCEL | SDL_SRCCOLORKEY, key);

            SDL_SetAlpha(m_surface, SDL_SRCALPHA | SDL_RLEACCEL, 0);
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
