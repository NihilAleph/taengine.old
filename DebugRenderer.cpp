#include "DebugRenderer.h"

// Contants and shaders
const float PI = 3.14159265359f;

namespace {
	const char* VERT_SRC = R"(#version 130
//The vertex shader operates on each vertex
//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
out vec2 fragmentPosition;
out vec4 fragmentColor;
uniform mat4 P;
void main() {
    //Set the x,y position on the screen
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
})";

	const char* FRAG_SRC = R"(#version 130
//The fragment shader operates on each pixel in a given polygon
in vec2 fragmentPosition;
in vec4 fragmentColor;
//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;
void main() {
    color = fragmentColor;
})";
}

namespace taengine {
	DebugRenderer::DebugRenderer()
	{
	}


	DebugRenderer::~DebugRenderer()
	{
		dispose();
	}


	void DebugRenderer::init() {

		// Shader init
		m_program.compileShadersFromSource(VERT_SRC, "DebugRendererVert", FRAG_SRC, "DebugRendererFrag");
		m_program.addAttribute("vertexPosition");
		m_program.addAttribute("vertexColor");
		m_program.linkShaders();

		// set up buffers
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

		glBindVertexArray(0);
	}

	void DebugRenderer::end() {
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload data
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(DebugVertex), m_vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload data
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_indices.size() * sizeof(DebugVertex), m_indices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_numElements = m_indices.size();
		m_indices.clear();
		m_vertices.clear();
	}


	glm::vec2 rotatePoint(const glm::vec2& point, float angle) {
		glm::vec2 newPoint;

		newPoint.x = point.x * cos(angle) - point.y * sin(angle);
		newPoint.y = point.x * sin(angle) + point.y * cos(angle);

		return newPoint;
	}

	void DebugRenderer::drawBox(const glm::vec4& destinationRectangle, const Color& color, float angle) {

		int start = m_vertices.size();
		m_vertices.resize(start + 4);

		glm::vec2 halfDimensions(destinationRectangle.z / 2.0f, destinationRectangle.w / 2.0f);
		glm::vec2 positionOffset(destinationRectangle.x, destinationRectangle.y);

		// get points centered in origin
		glm::vec2 tl(-halfDimensions.x, halfDimensions.y);
		glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
		glm::vec2 tr(halfDimensions.x, halfDimensions.y);
		glm::vec2 br(halfDimensions.x, -halfDimensions.y);

		// rotate points and translate so de origin is bl
		m_vertices[start].position = rotatePoint(tl, angle) + halfDimensions + positionOffset;
		m_vertices[start + 1].position = rotatePoint(bl, angle) + halfDimensions + positionOffset;
		m_vertices[start + 2].position = rotatePoint(br, angle) + halfDimensions + positionOffset;
		m_vertices[start + 3].position = rotatePoint(tr, angle) + halfDimensions + positionOffset;

		for (int j = start; j < start + 4; j++) {
			m_vertices[j].color = color;
		}

		m_indices.reserve(m_indices.size() + 8);

		m_indices.push_back(start);
		m_indices.push_back(start + 1);

		m_indices.push_back(start + 1);
		m_indices.push_back(start  + 2);

		m_indices.push_back(start + 2);
		m_indices.push_back(start + 3);

		m_indices.push_back(start + 3);
		m_indices.push_back(start);
	}

	void DebugRenderer::drawCircle(const glm::vec2& center, const Color& color, float radius) {
		static const int NUM_VERTICES = 100;
		
		int start = m_vertices.size();
		
		m_vertices.resize(start + NUM_VERTICES);
		// Set up vertices
		for (int i = 0; i < NUM_VERTICES; i++) {
			float angle = ((float)i / NUM_VERTICES) * 2.0f * PI;
			m_vertices[start + i].position.x = center.x + cos(angle) * radius;
			m_vertices[start + i].position.y = center.y + sin(angle) * radius;
			m_vertices[start + i].color = color;
		}

		// Set up indices for indexed drawing
		m_indices.reserve(m_indices.size() + NUM_VERTICES * 2);
		for (int i = 0; i < NUM_VERTICES - 1; i++) {
			m_indices.push_back(start + i);
			m_indices.push_back(start + i + 1);
		}

		m_indices.push_back(start + NUM_VERTICES - 1);
		m_indices.push_back(start);
	}

	void DebugRenderer::render(const glm::mat4& projectionMatrix, float lineWidth) {
		m_program.use();


		GLint pUniform = m_program.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		glLineWidth(lineWidth);
		glBindVertexArray(m_vao);
		glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		m_program.unuse();
	}

	void DebugRenderer::dispose() {
		if (m_vao) {
			glDeleteVertexArrays(1, &m_vao);
		}
		if (m_vbo) {
			glDeleteBuffers(1, &m_vbo);
		}
		if (m_ibo) {
			glDeleteBuffers(1, &m_ibo);
		}

		m_program.dispose();
	}

}