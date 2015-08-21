#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <string>
#include "GLTexture.h"


namespace taengine {
    class Sprite
    {
        public:
            Sprite();
            ~Sprite();

            void init(float x, float y, float width, float height, std::string texturePath);
            void draw();

        protected:
        private:

            // normalized coordinates
            float m_x;
            float m_y;
            float m_width;
            float m_height;

            GLuint m_vboID;
            GLTexture m_texture;
    };
}

#endif // SPRITE_H
