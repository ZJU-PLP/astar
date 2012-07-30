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

#ifndef MATRIX_ELEMENTS_HPP
#define MATRIX_ELEMENTS_HPP

template <typename T>
class Element {
public:

    virtual T grass() = 0;

    virtual T forest() = 0;

    virtual T water() = 0;

    virtual T empty() = 0;

    virtual T outsider() = 0;
};

template <typename T>
class AsciiToElement {
public:
    T execute(char ch) {
        switch (ch) {
            case 'G':
                return Element<T>().grass();

            case 'F':
                return Element<T>().forest();

            case 'W':
                return Element<T>().water();

            case '.':
            default:
                return Element<T>().empty();

        }
    }
};

template <typename T>
bool elementIsWalkable(const T& t) {
    if (t == Element<T>().grass()) {
        return true;
    }

    if (t == Element<T>().empty()) {
        return true;
    }

    return false;
}

#endif /* MATRIX_ELEMENTS_HPP */
