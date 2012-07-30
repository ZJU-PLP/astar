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

#ifndef GAME_IMAGELOADER_HPP
#define GAME_IMAGELOADER_HPP

#include <map>

#include <common/ResourceFinder.hpp>

#include "Image.hpp"

namespace Game {

class ImageLoader {
public:
    ImageLoader() :
        m_imageMap() {
    }

    Image& getImage(const std::string& fileName) {
        if (hasExistingImage(fileName)) {
	    return getExistingImage(fileName);
	} else {
	    return loadImage(fileName);
	}
    }

    ~ImageLoader() {
	ImageMap::iterator it(
	    m_imageMap.begin()
        );

	for (; it != m_imageMap.end(); ++it) {
	    if (it->second) {
		delete it->second;
	    }
	}
    }

private:
    const bool hasExistingImage(const std::string& fileName) const {
	return (m_imageMap.find(fileName) != m_imageMap.end());
    }

    Image& getExistingImage(const std::string& fileName) {
	return *(m_imageMap[fileName]);
    }

    Image& loadImage(const std::string& fileName) {
        const std::string path(ResourceFinder::findResource(fileName));

	m_imageMap[fileName] = new Image(path);

	return *m_imageMap[fileName];
    }

    typedef std::map<std::string, Image*> ImageMap;

    ImageMap m_imageMap;
};

} // Game

#endif // GAME_IMAGELOADER_HPP
