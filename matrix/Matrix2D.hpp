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

#include <common/Point2D.hpp>

#include <matrix/Element.hpp>

template <typename T>
class Matrix2D {
public:
    Matrix2D(int height, int width) :
        m_dim(height, width),
        m_matrix(NULL)
    {
        m_matrix = new T[m_dim.height * m_dim.width];

        reset();
    }

    Matrix2D() :
        m_dim(),
        m_matrix(NULL)
    {
    }

    void resize(const Dim2D& dim) {
        m_dim = dim;

        if (m_matrix != NULL) {
            delete [] m_matrix;
        }

        m_matrix = new T[m_dim.height * m_dim.width];

        reset();
    }

    ~Matrix2D() {
        delete [] m_matrix;
    }

    int getHeight() const {
        return m_dim.height;
    }

    int getWidth() const {
        return m_dim.width;
    }

    T get(const Point2D& p) const {
        if (withinBounds(p)) {
            return m_matrix[coord2index(p)];
        }

        return Element<T>().outsider();
    }

    void set(const Point2D& p, T type) {
        if (withinBounds(p)) {
            m_matrix[coord2index(p)] = type;
        }
    }

    void reset() {
        for (int i = 0; i < (m_dim.width * m_dim.height); ++i) {
             m_matrix[i] = Element<T>().empty();
        }
    }

    bool isEmpty(const Point2D& p) const {
        return (get(p) == Element<T>().empty());
    }

    bool withinBounds(const Point2D& p) const {
        if (0 <= p.x && 0 <= p.y) {
            if (p.x < m_dim.width && p.y < m_dim.height) {
                return true;
            }
        }

        return false;
    }

private:
    int coord2index(const Point2D& p) const {
        return p.y * m_dim.width + p.x;
    }

    Dim2D      m_dim;
    T*         m_matrix;
};

#endif /* MATRIX_MATRIX2D_HPP */
