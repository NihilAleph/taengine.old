#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>


namespace taengine {
    Sprite::Sprite() {
        m_vboID = 0;
    }

    Sprite::~Sprite() {
        if (m_vboID != 0) {
            glDeleteBuffers(1, &m_vboID);
        }
    }

    void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;

        m_texture = ResourceManager::getTexture(texturePath);

        if (m_vboID == 0) {
            glGenBuffers(1, &m_vboID);
        }

        // a square = 2 triangles * 2 coordinates (6*2)
        Vertex vertexData[6];

        // first triangle
        vertexData[0].setPosition(x + width, y + height);
        vertexData[0].setUV(1.0f, 1.0f);

        vertexData[1].setPosition(x, y + height);
        vertexData[1].setUV(0.0f, 1.0f);

        vertexData[2].setPosition(x, y);
        vertexData[2].setUV(0.0f, 0.0f);

        // second triangle
        vertexData[3].setPosition(x, y);
        vertexData[3].setUV(0.0f, 0.0f);

        vertexData[4].setPosition(x + width, y);
        vertexData[4].setUV(1.0f, 0.0f);

        vertexData[5].setPosition(x + width, y + height);
        vertexData[5].setUV(1.0f, 1.0f);

        for (int i = 0; i < 6; i++) {
            vertexData[i].setColor(255,0,255,255);
        }


        vertexData[1].setColor(0,0,255,255);

        vertexData[4].setColor(255,0,0,255);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // unbinding buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::draw() {

        glBindTexture(GL_TEXTURE_2D, m_texture.id);


        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        // unbinding buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
