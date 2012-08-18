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

#include "Background.hpp"

namespace {
    const std::string FOREST_TILE_PATH("forest.png");
    const std::string GRASS_TILE_PATH("grass.png");
    const std::string WATER_TILE_PATH("water.png");
}

namespace Game {

Background::Background(ImageLoader& loader, Matrix2D<TileType>* matrixPointer) :
    m_matrixPointer(matrixPointer),
    m_tileMap(),
    m_offsetx(0),
    m_offsety(0),
    m_h(0),
    m_w(0)
{
    m_tileMap[TileType_FOREST] = &loader.getImage(FOREST_TILE_PATH);
    m_tileMap[TileType_GRASS]  = &loader.getImage(GRASS_TILE_PATH);
    m_tileMap[TileType_WATER]  = &loader.getImage(WATER_TILE_PATH);

    /* Pick the width and height of the first tile, assume they are all equally sized */
    m_h = m_tileMap.begin()->second->getHeight();
    m_w = m_tileMap.begin()->second->getWidth();

    std::cout << "Loaded images" << std::endl;
}

void Background::scrollX(int delta) {
    m_offsetx += delta;
}

void Background::scrollY(int delta) {
    m_offsety += delta;
}

void Background::blit(SDL_Surface* destSurface) {
    const int screenWidth  = destSurface->w;
    const int screenHeight = destSurface->h;

    for (int i = 0; i < m_matrixPointer->getHeight(); ++i) {
        for (int j = 0; j < m_matrixPointer->getWidth(); ++j) {
            TileType type = m_matrixPointer->get(Point2D(i, j));

            if (m_tileMap.find(type) == m_tileMap.end()) {
                std::stringstream ss;
                ss << "Failed to load TileType at i=" << i << " j=" << j << " with enum value " << type;

                throw Exception(ss.str());
            }

            Image* image = m_tileMap[type];

            int y = m_offsety + ( m_h / 4) * i + (m_h / 4) * j;
            int x = m_offsetx + (-m_w / 2) * i + (m_w / 2) * j;

            SDL_Rect box = {x, y, image->getWidth(), image->getHeight()};
            SDL_BlitSurface(image->getSdlSurface(), NULL, destSurface, &box);
        }
    }
}

Point2D Background::screenCoordsToMatrixIndex(const Point2D& screenPoint) {
    int y = screenPoint.y - m_offsety - m_h / 2;
    int x = screenPoint.x - m_offsetx - m_w / 2;

    int det = (m_h / 4) * (m_w / 2) + (m_h / 4) * (m_w / 2);

    int i = ((m_w / 2) * y + -(m_h / 4) * x) / det;
    int j = ((m_w / 2) * y +  (m_h / 4) * x) / det;

    return Point2D(i, j);
}

} // Game
