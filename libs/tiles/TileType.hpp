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

#ifndef MATRIX_TILETYPE_HPP
#define MATRIX_TILETYPE_HPP

#include <stdint.h>

#include <matrix/Element.hpp>

enum TileEnum {
    TileEnum_OUTSIDE = -1,
    TileEnum_NONE,
    TileEnum_GRASS,
    TileEnum_FOREST,
    TileEnum_WATER
};

enum PartEnum {
    PartEnum_NONE         = 0,
    PartEnum_TOP_RIGHT    = (1 << 0),
    PartEnum_RIGHT        = (1 << 1),
    PartEnum_BOTTOM_RIGHT = (1 << 2),
    PartEnum_BOTTOM       = (1 << 3),
    PartEnum_BOTTOM_LEFT  = (1 << 4),
    PartEnum_LEFT         = (1 << 5),
    PartEnum_TOP_LEFT     = (1 << 6),
    PartEnum_TOP          = (1 << 7),
    PartEnum_ALL          = 0xff
};

struct Tile_s {
    Tile_s() :
        tile(TileEnum_NONE),
        part(PartEnum_NONE)
    {
    }

    Tile_s(TileEnum tile) :
        tile(tile),
        part(PartEnum_ALL)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Tile_s& tile) {
        os << "tile=" << tile.tile << " part=" << tile.part;
        return os;
    }

    bool operator==(const Tile_s& other) const {
        if (tile == other.tile) {
            if (part == other.part) {
                return true;
            }
        }

        return false;
    }

    bool operator!=(const Tile_s& other) const {
        return !(other == *this);
    }

    bool operator<(const Tile_s& other) const {
        if (tile == other.tile) {
            return part < other.part;
        } else {
            return tile < other.tile;
        }
    }

    uint8_t tile;
    uint8_t part;
};

struct TileAndOverlay_s {
    TileAndOverlay_s() :
        primary(),
        overlay()
    {
    }
    TileAndOverlay_s(TileEnum primaryTile) :
        primary(primaryTile),
        overlay()
    {
    }

    bool operator<(const TileAndOverlay_s& other) const {
        if (primary == other.primary) {
            return overlay < other.overlay;
        } else {
            return primary < other.primary;
        }
    }

    bool operator==(const TileAndOverlay_s& other) const {
        if (primary == other.primary) {
            return overlay == other.overlay;
        }

        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const TileAndOverlay_s& tileAndOverlay) {
        os << "primary=" << tileAndOverlay.primary << " overlay=" << tileAndOverlay.overlay;
        return os;
    }

    Tile_s primary;
    Tile_s overlay;
};

template <>
class Element<TileEnum> {
public:
    TileEnum  empty() {
        return TileEnum_NONE;
    }

    TileEnum  outsider() {
        return TileEnum_OUTSIDE;
    }

    TileEnum  grass() {
        return TileEnum_GRASS;
    }

    TileEnum  forest() {
        return TileEnum_FOREST;
    }

    TileEnum  water() {
        return TileEnum_WATER;
    }
};

template <>
class Element<Tile_s> {
public:
    Tile_s  empty() {
        return TileEnum_NONE;
    }

    Tile_s  outsider() {
        return TileEnum_OUTSIDE;
    }

    Tile_s  grass() {
        return TileEnum_GRASS;
    }

    Tile_s  forest() {
        return TileEnum_FOREST;
    }

    Tile_s  water() {
        return TileEnum_WATER;
    }
};

template <>
class Element<TileAndOverlay_s> {
public:
    TileAndOverlay_s empty() {
        return TileEnum_NONE;
    }

    TileAndOverlay_s outsider() {
        return TileEnum_OUTSIDE;
    }

    TileAndOverlay_s grass() {
        return TileEnum_GRASS;
    }

    TileAndOverlay_s forest() {
        return TileEnum_FOREST;
    }

    TileAndOverlay_s water() {
        return TileEnum_WATER;
    }
};

#endif /* MATRIX_TILETYPE_HPP */
