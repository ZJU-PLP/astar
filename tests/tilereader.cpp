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

#define RTEST_SKIP_PREFIX

#include <rtest/rtest.hpp>

#include <tiles/TileType.hpp>
#include <tiles/TileReader.hpp>

#include <matrix/Matrix2D.hpp>

TEST(tilereader, load_small) {
    std::string path("tests/data/matrix_small");
    ASSERT_TRUE(boost::filesystem::exists(path));

    Matrix2D<Tile_s> matrix;
    TileReader<Tile_s> reader;

    ASSERT_TRUE(reader.load(path, matrix));

    ASSERT_EQ(3, matrix.getWidth());
    ASSERT_EQ(2, matrix.getHeight());

    ASSERT_EQ(Tile_s(TileEnum_FOREST), matrix.get(Point2D(0, 0)));
    ASSERT_EQ(Tile_s(TileEnum_GRASS),  matrix.get(Point2D(0, 1)));
    ASSERT_EQ(Tile_s(TileEnum_WATER),  matrix.get(Point2D(0, 2)));

    ASSERT_EQ(Tile_s(TileEnum_GRASS),  matrix.get(Point2D(1, 0)));
    ASSERT_EQ(Tile_s(TileEnum_WATER),  matrix.get(Point2D(1, 1)));
    ASSERT_EQ(Tile_s(TileEnum_WATER),  matrix.get(Point2D(1, 2)));
}
