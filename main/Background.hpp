#ifndef GAME_BACKGROUND_HPP
#define GAME_BACKGROUND_HPP

#include <sstream>

#include <SDL.h>

#include <tiles/TileType.hpp>

#include "Image.hpp"

namespace {
    const std::string FOREST_TILE_PATH("forest.png");
    const std::string GRASS_TILE_PATH("grass.png");
    const std::string WATER_TILE_PATH("water.png");
}

namespace Game {

class Background {
public:
    Background(ImageLoader& loader, Matrix2D<TileType>* matrixPointer) :
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

    void scrollX(int delta) {
        m_offsetx += delta;
    }

    void scrollY(int delta) {
        m_offsety += delta;
    }

    void blit(SDL_Surface* destSurface) {
        const int screenWidth  = destSurface->w;
        const int screenHeight = destSurface->h;

        Image* image = NULL;

        for (int i = 0; i < m_matrixPointer->getHeight(); ++i) {
            for (int j = 0; j < m_matrixPointer->getWidth(); ++j) {
                TileType type = m_matrixPointer->get(Point2D(i, j));

                if (m_tileMap.find(type) == m_tileMap.end()) {
                    std::stringstream ss;
                    ss << "Failed to load TileType at i=" << i << " j=" << j << " with enum value " << type;

                    throw Exception(ss.str());
                }

                image = m_tileMap[type];

                int y = m_offsety + ( m_h / 4) * i + (m_h / 4) * j;
                int x = m_offsetx + (-m_w / 2) * i + (m_w / 2) * j;

                SDL_Rect box = {x, y, image->getWidth(), image->getHeight()};
                SDL_BlitSurface(image->getSdlSurface(), NULL, destSurface, &box);
            }
        }
    }

    Point2D screenCoordsToMatrixIndex(const Point2D& screenPoint) {
        int y = screenPoint.y - m_offsety - m_h / 2;
        int x = screenPoint.x - m_offsetx - m_w / 2;

        int det = (m_h / 4) * (m_w / 2) + (m_h / 4) * (m_w / 2);

        int i = ((m_w / 2) * y + -(m_h / 4) * x) / det;
        int j = ((m_w / 2) * y +  (m_h / 4) * x) / det;

        return Point2D(i, j);
    }

private:
    Matrix2D<TileType>*        m_matrixPointer;
    std::map<TileType, Image*> m_tileMap; /* Don't free images, they are owned by ImageLoader */
    int                        m_offsetx;
    int                        m_offsety;
    int                        m_h;
    int                        m_w;
};

} // Game

#endif // GAME_BACKGROUND_HPP
