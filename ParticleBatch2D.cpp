#include "ParticleBatch2D.h"

#include <iostream>
namespace taengine {



	ParticleBatch2D::ParticleBatch2D()
	{
	}


	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] m_particles;
	}


	void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc /* = defaultUpdateFunc */) {

		m_maxParticles = maxParticles;
		m_particles = new Particle2D[maxParticles];
		
		m_decayRate = decayRate;
		m_texture = texture;

		m_updateFunc = updateFunc;
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity,
		const Color color,
		float width) {

		int index = findFreePartice();

		auto& particle = m_particles[index];

		particle.life = 1.0f;
		particle.position = position;
		particle.velocity = velocity;
		particle.color = color;
		particle.width = width;
	}


	void ParticleBatch2D::update(float deltaTime) {
		for (int i = 0; i < m_maxParticles; i++) {
			if (m_particles[i].life > 0.0f) {
				m_updateFunc(m_particles[i], deltaTime);
				m_particles[i].life -= m_decayRate * deltaTime;


			}
		}
	}
	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
		glm::vec4 uvRectangle(0.0f, 0.0f, 1.0f, 1.0f);
		for (int i = 0; i < m_maxParticles; i++) {
			if (m_particles[i].life > 0.0f) {

				glm::vec4 destinationRectangle(m_particles[i].position.x, m_particles[i].position.y,
					m_particles[i].width, m_particles[i].width);

				spriteBatch->draw(destinationRectangle, uvRectangle, 0.0f, m_texture.id, m_particles[i].color);


			}
		}

	}

	int ParticleBatch2D::findFreePartice() {
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}

		}

		// No particles are free, overright first particle
		return 0;
	}
}