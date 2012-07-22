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

#include <matrix/Matrix2D.hpp>

#include <walkers/AStarWalker.hpp>

#define PRINT_WALK

TEST(matrixtest, set_and_get) {
    Matrix2D<TileType> matrix(4, 5);

    ASSERT_EQ(
        TileType_NONE,
        matrix.get(Point2D(3,2))
    );

    matrix.set(Point2D(3, 2), TileType_SOLID);

    ASSERT_EQ(
        TileType_SOLID,
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

TEST(astarwalker, walk_noblock) {
    Matrix2D<TileType> matrix(4, 4);
    matrix.set(Point2D(2, 2), TileType_SOLID);

    AStarWalker<TileType> walker(matrix);

    std::vector<Point2D> reconVec;
    int numVisited = 0;

    walker.run(Point2D(0, 0), Point2D(3, 3), reconVec, numVisited);

    ASSERT_TRUE(numVisited <= 7);
    ASSERT_TRUE(reconVec.size() <= 6);

    #ifdef PRINT_WALK
    walker.printDistances(reconVec);
    #endif
}

TEST(astarwalker, walk_blocker) {
    const size_t w = 20;
    const size_t h = w;

    Matrix2D<TileType> matrix(h, w);

    for (int x = 2; x <= w - 4; ++x) {
        matrix.set(Point2D(h / 2 - 1, x), TileType_SOLID);
    }

    for (int y = h/2 - 2; y <= h/2 - 1; ++y) {
        matrix.set(Point2D(y, 2), TileType_SOLID);
        matrix.set(Point2D(y, w - 3), TileType_SOLID);
    }

    AStarWalker<TileType> walker(matrix);

    std::vector<Point2D> reconVec;
    int numVisited = 0;

    ASSERT_TRUE(walker.run(Point2D(0, 3), Point2D(h - 1, w - 3), reconVec, numVisited));

    ASSERT_TRUE(reconVec.size() <= 29);
    ASSERT_TRUE(numVisited      <= 120);

    #ifdef PRINT_WALK
    walker.printDistances(reconVec);
    #endif
}

TEST(astarwalker, walk_blocker_fail) {
    const size_t w = 20;
    const size_t h = w;

    Matrix2D<TileType> matrix(h, w);

    for (int x = 0; x <= w - 1; ++x) {
        matrix.set(Point2D(h / 2 - 1, x), TileType_SOLID);
    }

    AStarWalker<TileType> walker(matrix);

    std::vector<Point2D> reconVec;
    int numVisited = 0;

    ASSERT_FALSE(walker.run(Point2D(0, 3), Point2D(h - 1, w - 3), reconVec, numVisited));
}

TEST(astarwalker, walk_maze) {
    const size_t w = 6;
    const size_t h = w;

    Matrix2D<TileType> matrix(h, w);
    matrix.set(Point2D(1, 0), TileType_SOLID);
    matrix.set(Point2D(1, 1), TileType_SOLID);
    matrix.set(Point2D(1, 2), TileType_SOLID);
    matrix.set(Point2D(1, 4), TileType_SOLID);
    matrix.set(Point2D(1, 5), TileType_SOLID);

    for (int i = 1; i < w; ++i)
        matrix.set(Point2D(3, i), TileType_SOLID);

    AStarWalker<TileType> walker(matrix);

    std::vector<Point2D> reconVec;
    int numVisited = 0;

    ASSERT_TRUE(walker.run(Point2D(0, 0), Point2D(h - 1, w - 2), reconVec, numVisited));

    ASSERT_TRUE(reconVec.size() <= 15);
    ASSERT_TRUE(numVisited      <= 20);

    #ifdef PRINT_WALK
    walker.printDistances(reconVec);
    #endif
}

int main() {
    RTest::runAllTests();
    return 0;
}
