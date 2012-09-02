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

#ifndef MATRIX_MAPREADER_HPP
#define MATRIX_MAPREADER_HPP

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/scoped_ptr.hpp>

#include <common/Dim2D.hpp>
#include <common/ResourceFinder.hpp>

#include <matrix/Matrix2D.hpp>

template <typename T>
class MapReader {
public:
    MapReader() {
    }

    bool load(const std::string& filename, Matrix2D<T>& outMatrix) {
        const std::string path(ResourceFinder::findResource(filename));

        bool result = false;

        boost::filesystem::fstream stream(path);

        if (stream) {
            Dim2D dim;

            if (parseHeader(stream, dim)) {
                outMatrix.resize(dim);
                if (readRows(stream, dim, outMatrix)) {
                    result = true;
                }
            }
        }

        return result;
    }

    bool parseHeader(boost::filesystem::fstream& stream, Dim2D& outDim) {
        std::cout << "parseHeader" << std::endl;

        bool result = false;

        std::string line;
        if (std::getline(stream, line)) {
            std::vector<std::string> strs;
            boost::split(strs, line, boost::is_any_of(":"));

            std::cout << "strs.size() = " << strs.size() << std::endl;

            if (!strs.empty()) {
                if (strs[0] == "rtsmap") {
                    std::cout << "Got rtsmap" << std::endl;

                    for (int i = 1; i < strs.size(); ++i) {
                        const std::string s(strs[i]);

                        if (boost::algorithm::starts_with(s, "h=")) {
                            std::string param(s, 2);
                            std::cout << "param=" << param << std::endl;

                            outDim.height = std::atoi(param.c_str());

                            std::cout << "height=" << outDim.height << std::endl;
                            continue;
                        }

                        if (boost::algorithm::starts_with(s, "w=")) {
                            std::string param(s, 2);
                            std::cout << "param=" << param << std::endl;

                            outDim.width = std::atoi(param.c_str());
                            std::cout << "width=" << outDim.width << std::endl;
                            continue;
                        }
                    }

                    if (0 < outDim.height && 0 < outDim.width) {
                        std::cout << "0 < height && 0 < width" << std::endl;

                        result = true;
                    } else {
                        std::cout << "Failed to read height and width" << std::endl;
                    }
                }
            }
        }

        return result;
    }

    bool readRows(boost::filesystem::fstream& stream, const Dim2D& dim, Matrix2D<T>& outMatrix) {
        std::string line;

        for (int y = 0; y < dim.height; ++y) {
            if (!std::getline(stream, line)) {
                std::cout << "Failed to read line" << std::endl;
                return false;
            }

            boost::algorithm::trim(line);

            if (line.size() != dim.width) {
                return false;
            }

            for (int x = 0; x < dim.width; ++x) {
                outMatrix.set(Point2D(y, x), AsciiToElement<T>().execute(line[x]));
            }
        }

        return true;
    }

};

#endif /* MATRIX_MAPREADER_HPP */
