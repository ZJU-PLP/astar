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

#ifndef COMMON_POINT2D
#define COMMON_POINT2D

#include <iostream>

struct Point2D {
public:
    Point2D(int y, int x) :
        x(x),
        y(y)
    {
    }

    Point2D() :
        x(0),
        y(0)
    {
    }

    bool operator!=(const Point2D& other) const {
        return x != other.x || y != other.y;
    }

    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }

    int x;
    int y;
};

inline std::ostream& operator<<(std::ostream& os, const Point2D& p) {
    os << "y=" << p.y << " x=" << p.x;
    return os;
}

inline bool operator<(const Point2D& a, const Point2D& b) {
    if (a.x != b.x) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

#endif /* COMMON_POINT2D */
