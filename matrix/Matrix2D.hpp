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

#ifndef MATRIX_MATRIX2D_HPP
#define MATRIX_MATRIX2D_HPP

template <typename T>
class Matrix2D {
public:
    Matrix2D(int height, int width) :
        m_height(height),
        m_width(width),
        m_matrix(NULL)
    {
        m_matrix = new T[m_height * m_width];

        reset();
    }

    ~Matrix2D() {
        delete [] m_matrix;
    }

    int getHeight() const {
        return m_height;
    }

    int getWidth() const {
        return m_width;
    }

    T get(int y, int x) const {
        if (withinBounds(y, x)) {
            return m_matrix[coord2index(y, x)];
        }

        return Element<T>().outsider();
    }

    void set(int y, int x, T type) {
        if (withinBounds(y, x)) {
            m_matrix[coord2index(y, x)] = type;
        }
    }

    void reset() {
        for (int i = 0; i < (m_width * m_height); ++i) {
             m_matrix[i] = Element<T>().empty();
        }
    }

    bool isEmpty(int y, int x) const {
        return (get(y, x) == Element<T>().empty());
    }

    bool withinBounds(int y, int x) const {
        if (0 <= x && 0 <= y) {
            if (x < m_width && y < m_height) {
                return true;
            }
        }

        return false;
    }

private:
    int coord2index(int y, int x) const {
        return y * m_width + x;
    }

    int        m_height;
    int        m_width;
    T*         m_matrix;
};

#endif /* MATRIX_MATRIX2D_HPP */
