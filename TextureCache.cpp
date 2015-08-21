#include "TextureCache.h"
#include "ImageLoader.h"

namespace taengine {
    TextureCache::TextureCache()
    {
        //ctor
    }

    TextureCache::~TextureCache()
    {
        //dtor
    }

    GLTexture TextureCache::getTexture(std::string texturePath) {

        // lookup for texture in map
        auto mapIterator = m_textureMap.find(texturePath);

        // if the texture is not in the map, load it
        if (mapIterator == m_textureMap.end()) {
            // load the texture
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);

            m_textureMap.insert(make_pair(texturePath, newTexture));

            //std::cout << "Loaded texture!\n";

            return newTexture;
        } else {
            //std::cout << "Used cached texture!\n";
            return mapIterator->second;
        }
    }
}
