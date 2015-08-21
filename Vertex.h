#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>

namespace taengine {


    struct Color {
        Color() {
        }
        Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : red(r), green(g), blue(b), alpha(a) {
        }
        GLubyte red;
        GLubyte green;
        GLubyte blue;
        GLubyte alpha;
    };

    struct Vertex {
        // total of bytes in vertex is multiple of 4 for optimization
        struct Position {
            float x;
            float y;
        } position;

        Color color;

        // UV is to tell to OpenGL which part of the image has to be used for each triangle.
        struct UV {
            float u;
            float v;
        } uv;

        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        void setColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
            color.red = red;
            color.green = green;
            color.blue = blue;
            color.alpha = alpha;
        }

        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }
    };
}

#endif // VERTEX_H
