#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Sprite.h"
#include "Vertex.h"

namespace taengine {

    enum class GlyphSortType { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

    class Glyph {
    public:

        Glyph() { }

		// default constructor, doesnt take angle
		Glyph::Glyph(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
			float glyphDepth, GLuint glyphTexture, const Color& color);

		// constructor that does take angle
		Glyph::Glyph(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
			float glyphDepth, GLuint glyphTexture, const Color& color, float angle);
        
        GLuint texture;
        float depth;

        Vertex topLeft, bottomLeft, topRight, bottomRight;

	private:
		glm::vec2 rotatePoint(const glm::vec2& point, float angle);
    };

    class RenderBatch {
        public:
            RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {
            }
            GLuint offset;
            GLuint numVertices;
            GLuint texture;
    };

    class SpriteBatch
    {
        public:
            SpriteBatch();
            virtual ~SpriteBatch();

            void init();

            void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
            void end();

            // pointers for optimization and speed, though they should not be changed
            // rectangles have both position (x,y) and dimensions (z,w)
            void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, 
				float depth, GLuint texture, const Color& color);

			void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
				float depth, GLuint texture, const Color& color, float angle);

			void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
				float depth, GLuint texture, const Color& color, glm::vec2& direction);

            void renderBatch();
        protected:
        private:
            GLuint m_vboID;
            GLuint m_vaoID;

            // optimization for sorting vector
            std::vector<Glyph*> m_glyphPointers;
            // Actual glyphs for cache performance
            std::vector<Glyph> m_glyphs;
            GlyphSortType m_sortType;

            std::vector<RenderBatch> m_renderBatches;

            void createRenderBatches();

            void createVertexArray();
            void sortGlyphs();

            static bool compareBackToFront(Glyph* a, Glyph* b);
            static bool compareFrontToBack(Glyph* a, Glyph* b);
            static bool compareTexture(Glyph* a, Glyph* b);
    };
}
#endif // SPRITEBATCH_H
