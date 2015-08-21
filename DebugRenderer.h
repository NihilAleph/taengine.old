#pragma once

#include "GLSLProgram.h"
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>

namespace taengine {
	class DebugRenderer sealed
	{
	public:
		DebugRenderer();
		~DebugRenderer();

		void init();
		void end();

		void drawBox(const glm::vec4& destinationRectangle, const Color& color, float angle);
		void drawCircle(const glm::vec2& center, const Color& color, float radius);
		void render(const glm::mat4& projectionMatrix, float lineWidth);
		void dispose();

		struct DebugVertex {
			glm::vec2 position;
			taengine::Color color;
		};

	private:
		taengine::GLSLProgram m_program;
		std::vector<DebugVertex> m_vertices;
		std::vector<GLuint> m_indices;
		GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;

		int m_numElements = 0;

	};

}