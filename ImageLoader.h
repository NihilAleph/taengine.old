#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "GLTexture.h"
#include<string>

namespace taengine {
    class ImageLoader
    {
        public:
            static GLTexture loadPNG(std::string filePath);
        protected:
        private:
    };
}

#endif // IMAGELOADER_H
