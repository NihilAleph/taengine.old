#include "ResourceManager.h"

namespace taengine {
    TextureCache ResourceManager::m_textureCache;

    GLTexture ResourceManager::getTexture(std::string texturePath) {
        return m_textureCache.getTexture(texturePath);
    }
}
