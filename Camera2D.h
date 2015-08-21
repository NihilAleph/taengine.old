#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace taengine {
    class Camera2D
    {
        public:
            Camera2D();
            virtual ~Camera2D();

            void init(int screenWidth, int screenHeight);

            void update();

            glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

            bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

            void setPosition(const glm::vec2& newPosition) {
                m_position = newPosition;
                m_matrixUpdate = true;
            }
            void setScale(float newScale) {
                m_scale = newScale;
                m_matrixUpdate = true;
            }

            glm::vec2 getPosition() { return m_position; }
            float getScale() { return m_scale; }
            glm::mat4 getCameraMatrix() { return m_cameraMatrix; }
        protected:
        private:
            int m_screenWidth, m_screenHeight;
            glm::vec2 m_position;
            glm::mat4 m_cameraMatrix;
            glm::mat4 m_orthoMatrix;
            float m_scale;
            // if needs to update matrix
            bool m_matrixUpdate;
    };
}

#endif // CAMERA2D_H
