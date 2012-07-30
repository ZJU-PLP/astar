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
