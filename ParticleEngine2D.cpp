#include "ParticleEngine2D.h"

namespace taengine {
	ParticleEngine2D::ParticleEngine2D()
	{
		// empty
	}
	ParticleEngine2D::~ParticleEngine2D()
	{

		for (auto& it : m_particleBatches) {
			delete it;
		}
	}


	void ParticleEngine2D::addParticleBatch(ParticleBatch2D* particleBatch) {
		m_particleBatches.push_back(particleBatch);
	}

	void ParticleEngine2D::update(float deltaTime) {

		for (auto& it : m_particleBatches) {
			it->update(deltaTime);

		}
	}

	void ParticleEngine2D::draw(SpriteBatch* spriteBatch) {

		for (auto& it : m_particleBatches) {
			spriteBatch->begin();

			it->draw(spriteBatch);

			spriteBatch->end();
			spriteBatch->renderBatch();
		}
	}
}