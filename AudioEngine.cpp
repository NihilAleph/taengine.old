#include "AudioEngine.h"
#include "TaengineErrors.h"

namespace taengine {

	void SoundEffect::play(int loops) {
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
			if (Mix_PlayChannel(-0, m_chunk, loops) == -1) {
				fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
			}
		}
	}

	void Music::play(int loops) {
		if (Mix_PlayMusic(m_music, loops) == -1) {
			fatalError("Mix_PlayMusic error: " + std::string(Mix_GetError()));
		}
	}


	void Music::pause() {
		Mix_PauseMusic();
	}
	void Music::stop() {
		Mix_HaltMusic();
	}
	void Music::resume() {
		Mix_ResumeMusic();
	}

	
	AudioEngine::AudioEngine()
	{
	}


	AudioEngine::~AudioEngine() {
		destroy();

	}

	void AudioEngine::init() {
		if (m_isInitialized) {
			fatalError("Tried to initialize AudioEngine twice!");
		}
		// Parameter can be bitwise combination MIX_INITFAC,
		// MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
			fatalError("Mix_init error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			fatalError("Mix_init error: " + std::string(Mix_GetError()));
		}

		m_effectMap.clear();
		m_musicMap.clear();

		m_isInitialized = true;
	}

	void AudioEngine::destroy() {
		if (m_isInitialized) {
			m_isInitialized = false;

			for (auto& it : m_effectMap) {
				Mix_FreeChunk(it.second);
			}
			for (auto& it : m_musicMap) {
				Mix_FreeMusic(it.second);
			}

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
		// try to find audio in cache
		auto iterator = m_effectMap.find(filePath);

		SoundEffect soundEffect;

		if (iterator == m_effectMap.end()) {
			// failed to find
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			// check for errors
			if (chunk == nullptr) {
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
			}

			soundEffect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else {
			// its already cached
			soundEffect.m_chunk = iterator->second;
		}

		return soundEffect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath) {

		// try to find audio in cache
		auto iterator = m_musicMap.find(filePath);

		Music music;

		if (iterator == m_musicMap.end()) {
			// failed to find
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			// check for errors
			if (mixMusic == nullptr) {
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
			}

			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else {
			// its already cached
			music.m_music = iterator->second;
		}

		return music;
	}
}