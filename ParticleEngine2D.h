#pragma once

#include <vector>
#include "SpriteBatch.h"
#include "ParticleBatch2D.h"

namespace taengine {
	class ParticleEngine2D
	{
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		// after adding particle batch, the engine is responsible for deallotcation
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

	private:
		std::vector<ParticleBatch2D*> m_particleBatches;
	};
}
