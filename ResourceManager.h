#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"
#include <string>

namespace taengine {
    class ResourceManager
    {
        public:
            static GLTexture getTexture(std::string texturePath);
        protected:
        private:
            static TextureCache m_textureCache;
    };
}

#endif // RESOURCEMANAGER_H
