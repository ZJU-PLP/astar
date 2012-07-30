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

#ifndef COMMON_DIM2D
#define COMMON_DIM2D

#include <iostream>

struct Dim2D {
public:
    Dim2D(int height, int width) :
        width(width),
        height(height)
    {
    }

    Dim2D() :
        width(0),
        height(0)
    {
    }

    bool operator!=(const Dim2D& other) const {
        return width != other.width || height != other.height;
    }

    bool operator==(const Dim2D& other) const {
        return width == other.width && height == other.height;
    }

    int width;
    int height;
};

inline std::ostream& operator<<(std::ostream& os, const Dim2D& p) {
    os << "height=" << p.height << " width=" << p.width;
    return os;
}

inline bool operator<(const Dim2D& a, const Dim2D& b) {
    if (a.width != b.width) {
        return a.width < b.width;
    } else {
        return a.height < b.height;
    }
}

#endif /* COMMON_DIM2D */
