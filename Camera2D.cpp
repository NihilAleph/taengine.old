#include "Camera2D.h"
#include <algorithm>

namespace taengine {
    Camera2D::Camera2D() : m_position(0.0f,0.0f), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_matrixUpdate(true), m_screenWidth(500), m_screenHeight(500)
    {
        //ctor
    }

    Camera2D::~Camera2D()
    {
        //dtor
    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        m_orthoMatrix = glm::ortho(0.0f, (float) m_screenWidth, 0.0f, (float) m_screenHeight);
    }

    void Camera2D::update() {
        if (m_matrixUpdate) {
            glm::vec3 translate(-m_position.x + m_screenWidth/2, -m_position.y + m_screenHeight/2, 0.0f);
            m_cameraMatrix = glm::translate(m_orthoMatrix, translate);
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

            m_matrixUpdate = false;
        }
    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
        // invert y direction
        screenCoords.y = m_screenHeight - screenCoords.y;
        // make 0 the center
        screenCoords -= glm::vec2(m_screenWidth/2, m_screenHeight/2);
        // scale the coords
        screenCoords /= m_scale;
        // translate the coords
        screenCoords += m_position;

        return screenCoords;
    }

    // Simple AABB test to see if a box is in the camera view
    bool Camera2D::isBoxInView(const glm::vec2& centerPosition, const glm::vec2& dimensions) {
//
        glm::vec2 screenScaledDimensions = glm::vec2(m_screenWidth, m_screenWidth) / m_scale;
        // The minimum distance before a collision occurs
        const float MIN_DISTANCE_X = dimensions.x / 2.0f + screenScaledDimensions.x / 2.0f;
        const float MIN_DISTANCE_Y = dimensions.y / 2.0f + screenScaledDimensions.y / 2.0f;

        // Vector from the agent to the center of camera
        glm::vec2 distVec = centerPosition - m_position;

        // Get the depth of the collision
        float xDepth = MIN_DISTANCE_X - abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

        // If either the depths are > 0, then we collided
        if (xDepth > 0 && yDepth > 0) {
            return true;
        }

        return false;
    }
}
