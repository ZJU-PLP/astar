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

#ifndef GAME_BACKGROUND_HPP
#define GAME_BACKGROUND_HPP

#include <sstream>

#include <SDL.h>

#include <matrix/Matrix2D.hpp>

#include <tiles/TileType.hpp>

#include <image/ImageLoader.hpp>

namespace Game {

class Background {
public:
    Background(ImageLoader& loader, Matrix2D<TileAndOverlay_s>* matrixPointer);

    void scrollX(int delta);

    void scrollY(int delta);

    void blit(SDL_Surface* destSurface);

    Point2D screenCoordsToMatrixIndex(const Point2D& screenPoint);

private:
    Matrix2D<TileAndOverlay_s>*        m_matrixPointer;
    std::map<Tile_s, Image*> m_tileMap; /* Don't free images, they are owned by ImageLoader */
    int                        m_offsetx;
    int                        m_offsety;
    int                        m_h;
    int                        m_w;
};

} // Game

#endif // GAME_BACKGROUND_HPP
