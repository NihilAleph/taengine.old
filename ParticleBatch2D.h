#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

#include <functional>

namespace taengine {

	class Particle2D {
	public:

		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		Color color;
		// assume particle as square
		float width = 0.0f;
		float life = 0.0f;
	};

	inline void defaultUpdateFunc(Particle2D& particle, float deltaTime) {
		particle.position += particle.velocity * deltaTime;

	}

	class ParticleBatch2D
	{
	public:

		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc = defaultUpdateFunc);
		void addParticle(const glm::vec2& position, const glm::vec2& velocity, const Color color, float width);

		void update(float deltaTime);
		void draw(SpriteBatch* spriteBatch);
	private:
		// global attributes for particles
		float m_decayRate = 0.1f;
		// a big buffer for particles so we dont have to keep doing new and delete
		Particle2D* m_particles = nullptr;
		int m_maxParticles = 0;

		std::function<void(Particle2D&, float)> m_updateFunc;

		int m_lastFreeParticle = 0;

		GLTexture m_texture;

		int findFreePartice();
	};

}