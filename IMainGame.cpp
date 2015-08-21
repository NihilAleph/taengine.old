#include "IMainGame.h"
#include "Timing.h"

namespace taengine {

	IMainGame::IMainGame()
	{
		m_screenList = std::make_unique<ScreenList>(this);
	}


	IMainGame::~IMainGame()
	{
		// Empty
	}


	void IMainGame::run() {

		if (init() == false) {
			return;
		}

		m_isRunning = true;
		FPSLimiter fpsLimiter;

		fpsLimiter.setMaxFPS(60.0f);

		while (m_isRunning) {
			fpsLimiter.begin();

			m_inputManager.update();
			update();

			if (m_isRunning) {
				draw();

				fpsLimiter.end();
				m_window.swapBuffer();
			}

		}

	}
	void IMainGame::exitGame() {
		m_currentScreen->onExit();
		if (m_screenList) {
			m_screenList->destroy();
			m_screenList.reset();
		}
		m_isRunning = false;
	}


	bool IMainGame::init() {
		taengine::init();

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		if (!initSystems()) return false;

		onInit();

		addScreens();

		m_currentScreen = m_screenList->getCurrent();
		m_currentScreen->onEntry();
		m_currentScreen->setRunning();

		return true;

	}
	bool IMainGame::initSystems() {
		m_window.create("Default", 900,600,0);

		return true;
	}


	void IMainGame::update() {
		if (m_currentScreen) {
			switch (m_currentScreen->getState()) {
			case ScreenState::RUNNING :
				m_currentScreen->update();
				break;
			case ScreenState::CHANGE_NEXT :
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveNext();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
				}
				break;
			case ScreenState::CHANGE_PREVIOUS :
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->movePrevious();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
				}
				break;
			case ScreenState::EXIT_APPLICATION :
				exitGame();
				break;
			default:
				break;
			}
		}
		else {
			exitGame();
		}
	}
	void IMainGame::draw() {
		glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
			m_currentScreen->draw();
		}
	}


	void IMainGame::onSDLEvent(SDL_Event& sdlEvent) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords((float)sdlEvent.motion.x, (float)sdlEvent.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(sdlEvent.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(sdlEvent.button.button);
			break;
		}
	}

}