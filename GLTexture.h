#ifndef GLTEXTURE_H_INCLUDED
#define GLTEXTURE_H_INCLUDED

#include<GL/glew.h>

namespace taengine {
    class GLTexture {
	public:
        GLuint id;
        int width;
        int height;
    };
}

#endif // GLTEXTURE_H_INCLUDED
