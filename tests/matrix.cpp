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

#include <walkers/AStarWalker.hpp>

TEST(matrixtest, set_and_get) {
    Matrix2D<TileType> matrix(4, 5);

    ASSERT_EQ(
        TileType_NONE,
        matrix.get(Point2D(3,2))
    );

    matrix.set(Point2D(3, 2), TileType_FOREST);

    ASSERT_EQ(
        TileType_FOREST,
        matrix.get(Point2D(3,2))
    );

    ASSERT_EQ(
        TileType_OUTSIDE,
        matrix.get(Point2D(3, 5))
    );

    ASSERT_EQ(
        TileType_OUTSIDE,
        matrix.get(Point2D(-1, -1))
    );
}