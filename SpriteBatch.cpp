#include "SpriteBatch.h"
#include <algorithm>

namespace taengine {

	Glyph::Glyph(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, float glyphDepth,
		GLuint glyphTexture, const Color& color) {

		texture = glyphTexture;
		depth = glyphDepth;

		topLeft.color = color;
		topLeft.setPosition(destinationRectangle.x, destinationRectangle.y + destinationRectangle.w);
		topLeft.setUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destinationRectangle.x, destinationRectangle.y);
		bottomLeft.setUV(uvRectangle.x, uvRectangle.y);

		topRight.color = color;
		topRight.setPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y + destinationRectangle.w);
		topRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);

		bottomRight.color = color;
		bottomRight.setPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y);
		bottomRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

	}


	Glyph::Glyph(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, float glyphDepth, 
		GLuint glyphTexture, const Color& color, float angle) {

		glm::vec2 halfDimensions(destinationRectangle.z / 2.0f, destinationRectangle.w / 2.0f);

		// get points centered in origin
		glm::vec2 tl(-halfDimensions.x, halfDimensions.y);
		glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
		glm::vec2 tr(halfDimensions.x, halfDimensions.y);
		glm::vec2 br(halfDimensions.x, -halfDimensions.y);

		// rotate points and translate so de origin is bl
		tl = rotatePoint(tl, angle) + halfDimensions;
		bl = rotatePoint(bl, angle) + halfDimensions;
		tr = rotatePoint(tr, angle) + halfDimensions;
		br = rotatePoint(br, angle) + halfDimensions;

		texture = glyphTexture;
		depth = glyphDepth;

		topLeft.color = color;
		topLeft.setPosition(destinationRectangle.x + tl.x, destinationRectangle.y + tl.y);
		topLeft.setUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destinationRectangle.x + bl.x, destinationRectangle.y + bl.y);
		bottomLeft.setUV(uvRectangle.x, uvRectangle.y);

		topRight.color = color;
		topRight.setPosition(destinationRectangle.x + tr.x,
			destinationRectangle.y + tr.y);
		topRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);

		bottomRight.color = color;
		bottomRight.setPosition(destinationRectangle.x + br.x, destinationRectangle.y + br.y);
		bottomRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

	}

	glm::vec2 Glyph::rotatePoint(const glm::vec2& point, float angle) {
		glm::vec2 newPoint;

		newPoint.x = point.x * cos(angle) - point.y * sin(angle);
		newPoint.y = point.x * sin(angle) + point.y * cos(angle);

		return newPoint;
	}

    SpriteBatch::SpriteBatch() : m_vboID(0), m_vaoID(0)
    {
        //ctor
    }

    SpriteBatch::~SpriteBatch()
    {
        //dtor
    }

    void SpriteBatch::init() {
        createVertexArray();
    }

    void SpriteBatch::begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/) {
        m_sortType = sortType;
        m_renderBatches.clear();

        m_glyphs.clear();
    }

    void SpriteBatch::end() {
        m_glyphPointers.resize(m_glyphs.size());
        for (int i = 0; i < m_glyphs.size(); i++) {
            m_glyphPointers[i] = &m_glyphs[i];
        }
        sortGlyphs();
        createRenderBatches();
    }

    void SpriteBatch::renderBatch() {

        glBindVertexArray(m_vaoID);

        for (int i = 0; i < m_renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

            glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
        }

        glBindVertexArray(0);
    }

    void SpriteBatch::createRenderBatches() {
        std::vector<Vertex> vertices;
        // reserve 6 vertices per glyph in memory for vertices
        vertices.resize(m_glyphPointers.size() * 6);

        if (m_glyphPointers.empty()) {
            return;
        }

        int currentVertex = 0;
        // emplace initi    alize the object with the parameters in the construct of the class
        m_renderBatches.emplace_back(currentVertex, 6, m_glyphPointers[0]->texture);

        vertices[currentVertex++] = m_glyphPointers[0]->topLeft;
        vertices[currentVertex++] = m_glyphPointers[0]->bottomLeft;
        vertices[currentVertex++] = m_glyphPointers[0]->topRight;
        vertices[currentVertex++] = m_glyphPointers[0]->topRight;
        vertices[currentVertex++] = m_glyphPointers[0]->bottomRight;
        vertices[currentVertex++] = m_glyphPointers[0]->bottomLeft;

        for (int i = 1; i < m_glyphPointers.size(); i++) {
            if (m_glyphPointers[i]->texture != m_glyphPointers[i-1]->texture) {
                m_renderBatches.emplace_back(currentVertex, 6, m_glyphPointers[i]->texture);
            } else {
                m_renderBatches.back().numVertices += 6;
            }
            // emplace initi    alize the object with the parameters in the construct of the class
            vertices[currentVertex++] = m_glyphPointers[i]->topLeft;
            vertices[currentVertex++] = m_glyphPointers[i]->bottomLeft;
            vertices[currentVertex++] = m_glyphPointers[i]->topRight;
            vertices[currentVertex++] = m_glyphPointers[i]->topRight;
            vertices[currentVertex++] = m_glyphPointers[i]->bottomRight;
            vertices[currentVertex++] = m_glyphPointers[i]->bottomLeft;
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        // orphan the buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        // upload data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // This function binds the buffer setting to the Vertex array, so that when we call again vao we dont have to set
    void SpriteBatch::createVertexArray() {
        if (m_vaoID == 0) {
            glGenVertexArrays(1, &m_vaoID);
        }

        glBindVertexArray(m_vaoID);

        if (m_vboID == 0) {
            glGenBuffers(1, &m_vboID);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // this is the position attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

        // this is the color attribute pointer
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) offsetof(Vertex, color));

        // this is the color attribute pointer
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));


        glBindVertexArray(0);
    }


	void SpriteBatch::draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, float depth,
		GLuint texture, const Color& color) {

		m_glyphs.emplace_back(destinationRectangle, uvRectangle, depth, texture, color);
	}


	void SpriteBatch::draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, float depth,
		GLuint texture, const Color& color, float angle) {

		m_glyphs.emplace_back(destinationRectangle, uvRectangle, depth, texture, color, angle);
	}


	void SpriteBatch::draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, float depth,
		GLuint texture, const Color& color, glm::vec2& direction) {
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, direction));

		if (direction.y < 0) angle = -angle;

		m_glyphs.emplace_back(destinationRectangle, uvRectangle, depth, texture, color, angle);
	}


    void SpriteBatch::sortGlyphs(){
        switch(m_sortType) {
            case GlyphSortType::BACK_TO_FRONT:
                std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
                break;
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
                break;
            case GlyphSortType::TEXTURE:
                std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
                break;
        }
    }


    bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
        return a->depth < b->depth;
    }
    bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
        return a->depth < b->depth;
    }
    bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
        return a->texture < b->texture;
    }


}
