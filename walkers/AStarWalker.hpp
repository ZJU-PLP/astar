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

#ifndef WALKERS_ASTARWALKER_HPP
#define WALKERS_ASTARWALKER_HPP

#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <queue>

#include <common/Point2D.hpp>

#include <walkers/DistanceMatrix.hpp>

typedef std::pair<int, Point2D> DistancePoint;

class ChooseSmallestDistance : public std::binary_function<DistancePoint, DistancePoint, bool> {
public:
    inline bool operator()(const DistancePoint& dp1, const DistancePoint& dp2) {
        return dp1.first > dp2.first;
    }
};

template <typename T>
class AStarWalker {
public:
    AStarWalker(const Matrix2D<T>& matrix) :
        m_matrix(matrix),
        m_visited(matrix.getHeight(), matrix.getWidth()),
        m_toBeVisited(),
        m_startP()
    {
    }

    bool run(const Point2D& startP, const Point2D& endP, std::vector<Point2D>& outReconVec, int& numVisited) {
        m_startP = startP;
        m_visited.reset();

        m_toBeVisited.push(std::make_pair(1, startP));

        while (m_visited.isEmpty(endP)) {
            if (!m_toBeVisited.empty()) {
                DistancePoint currp = m_toBeVisited.top();
                m_toBeVisited.pop();

                if (!isVisited(currp.second)) {
                    m_visited.set(currp.second, currp.first);

                    walkStepsTowardsEnd(currp, endP);

                    addNeighboursIfUnvisited(currp);
                }

            } else {
                std::cout << "Nothing to pop" << std::endl;
                return false;
            }
        }

        numVisited = 0;
        if (reconstructPath(startP, endP, outReconVec)) {
            for (int y = 0; y < m_visited.getHeight(); ++y) {
                for (int x = 0; x < m_visited.getWidth(); ++x) {
                    if (!m_visited.isEmpty(Point2D(y, x))) {
                        ++numVisited;
                    }
                }
            }

            return true;
        }

        return false;
    }

    void printDistances(const std::vector<Point2D>& reconVec) {
        const int NUM_ALPHAS = 26;

        for (int y = 0; y < m_matrix.getHeight(); ++y) {
            for (int x = 0; x < m_matrix.getWidth(); ++x) {
                if (std::find(reconVec.begin(), reconVec.end(), Point2D(y, x)) != reconVec.end()) {
                    std::cout << "@";
                } else if (!isWalkable(Point2D(y, x))) {
                    std::cout << "+";
                } else if (isVisited(Point2D(y, x))) {
                    std::cout << (char)('A' + (m_visited.get(Point2D(y, x)) % NUM_ALPHAS));
                } else {
                    std::cout << "_";
                }
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

private:

    bool reconstructPath(const Point2D& startP, const Point2D& endP, std::vector<Point2D>& outResult) {
        Point2D currPoint(endP);
        int     currValue = m_visited.get(endP);

        outResult.push_back(currPoint);

        while (1 < currValue) {
            const Point2D left(currPoint.y, currPoint.x - 1);
            if (checkIfValueIsLower(left, currPoint, currValue, outResult)) {
                continue;
            }

            const Point2D top(currPoint.y - 1, currPoint.x);
            if (checkIfValueIsLower(top, currPoint, currValue, outResult)) {
                continue;
            }

            const Point2D down(currPoint.y + 1, currPoint.x);
            if (checkIfValueIsLower(down, currPoint, currValue, outResult)) {
                continue;
            }

            const Point2D right(currPoint.y, currPoint.x + 1);
            if (checkIfValueIsLower(right, currPoint, currValue, outResult)) {
                continue;
            }

            return false;
        }

        std::reverse(outResult.begin(), outResult.end());

        optimizePath(outResult);

        return true;
    }

    void optimizePath(std::vector<Point2D>& resultPath) {
        if (resultPath.size() < 3) {
            /* Nothing to do */
            return;
        }

        for (int i = 0; i < (resultPath.size() - 2); ++i) {
            const Point2D& a = resultPath[i + 0];
            const Point2D& c = resultPath[i + 2];

            int diffacX = c.x - a.x;
            int diffacY = c.y - a.y;

            if (std::abs(diffacY) == 1 && std::abs(diffacX) == 1) {
                Point2D neigh1(a.y, c.x);
                Point2D neigh2(c.y, a.x);

                if (isWalkable(neigh1) && isWalkable(neigh2)) {
                    resultPath.erase(resultPath.begin() + i + 1);
                }
            }
        }
    }

    bool checkIfValueIsLower(const Point2D& newPoint, Point2D& currPoint, int& currValue, std::vector<Point2D>& outResult) {
        if (!m_visited.isEmpty(newPoint) && isWalkable(newPoint)) {
            int newValue = m_visited.get(newPoint);

            if (newValue < currValue) {
                currValue = newValue;
                currPoint = newPoint;

                outResult.push_back(currPoint);

                return true;
            }
        }

        return false;
    }


    bool walkStepsTowardsEnd(const DistancePoint& curr, const Point2D& endP) {
        DistancePoint newp(curr);

        while (walkOneStepTowardsEnd(newp, endP, newp)) {
            m_visited.set(newp.second, newp.first);

            addNeighboursIfUnvisited(newp);
        }
    }

    bool walkOneStepTowardsEnd(DistancePoint curr, const Point2D& endP, DistancePoint& outNewp) {
        int diffX = endP.x - curr.second.x;
        int diffY = endP.y - curr.second.y;

        DistancePoint alt1(curr);
        DistancePoint alt2(curr);

        alt1.first++;
        alt2.first++;

        if (!diffX && !diffY) {
            return false;
        }

        if (diffX && diffY) {
            alt1.second.x += (diffX / std::abs(diffX));
            alt2.second.y += (diffY / std::abs(diffY));

            if (std::abs(diffX) < std::abs(diffY)) {
                std::swap(alt1, alt2);
            }
        } else if (diffX && !diffY) {
            alt1.second.x += (diffX / std::abs(diffX));
            alt2 = alt1;
        } else if (!diffX && diffY) {
            alt1.second.y += (diffY / std::abs(diffY));
            alt2 = alt1;
        }

        if (isWalkableAndNotVisited(alt1.second)) {
            outNewp = alt1;
            return true;
        } else if (isWalkableAndNotVisited(alt2.second)) {
            outNewp = alt2;
            return true;
        }

        return false;
    }

    bool isWalkableAndNotVisited(const Point2D& p) {
        return isWalkable(Point2D(p.y, p.x)) && !isVisited(Point2D(p.y, p.x));
    }

    void addNeighboursIfUnvisited(const DistancePoint& currdp) {
        if (!isWalkable(currdp.second)) {
            return;
        }

        int     distance = currdp.first + 1;
        Point2D p        = currdp.second;

        const Point2D left(p.y, p.x - 1);
        addIfUnvisited(left, distance);

        const Point2D top(p.y - 1, p.x);
        addIfUnvisited(top, distance);

        const Point2D bottom(p.y + 1, p.x);
        addIfUnvisited(bottom, distance);

        const Point2D right(p.y, p.x + 1);
        addIfUnvisited(right, distance);
    }

    void addIfUnvisited(const Point2D& p, int distance) {
        if (!isVisited(Point2D(p.y, p.x))) {
            if (isWalkable(Point2D(p.y, p.x))) {
                m_toBeVisited.push(std::make_pair(distance, p));
            }
        }
    }

    bool isWalkable(const Point2D& p) const {
        return elementIsWalkable(m_matrix.get(p));
    }

    bool isVisited(const Point2D& p) {
        return !m_visited.isEmpty(p);
    }

    const Matrix2D<T>& m_matrix;

    DistanceMatrix m_visited;
    std::priority_queue<DistancePoint, std::vector<DistancePoint>, ChooseSmallestDistance > m_toBeVisited;
    Point2D m_startP;
};

#endif /* WALKERS_ASTARWALKER_HPP */
