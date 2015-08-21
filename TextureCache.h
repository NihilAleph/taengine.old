#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <map>
#include <string>
#include "GLTexture.h"

namespace taengine {
    class TextureCache
    {
        public:
            TextureCache();
            virtual ~TextureCache();
            GLTexture getTexture(std::string texturePath);
        protected:
        private:
            std::map<std::string, GLTexture> m_textureMap;
    };
}

#endif // TEXTURECACHE_H
