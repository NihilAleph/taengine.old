#pragma once
#include "GLTexture.h"
#include <glm\glm.hpp>

namespace taengine {
	class TileSheet {
	public:
		void init(const GLTexture& texture, const glm::ivec2& tileDimensions) {
			this->texture = texture;
			this->dimensions = tileDimensions;
		}

		glm::vec4 getUVs(int index) {
			int xTile = index % dimensions.x;
			int yTile = index / dimensions.x;

			glm::vec4 uvs;
			uvs.x = xTile / (float)dimensions.x;
			uvs.y = yTile / (float)dimensions.y;
			uvs.z = 1.0f / dimensions.x;
			uvs.w = 1.0f / dimensions.y;

			return uvs;
		}

		GLTexture texture;
		glm::ivec2 dimensions;
	};
}