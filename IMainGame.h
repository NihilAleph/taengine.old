#pragma once

#include <memory>
#include "taengine.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include "Window.h"
#include "InputManager.h"

namespace taengine {

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		

		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;

		const float getFps() const {
			return m_fps;
		}

		InputManager getInputManager() const { return m_inputManager; }

		void onSDLEvent(SDL_Event& sdlEvent);

	protected:
		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;

		bool m_isRunning = false;

		float m_fps = 0.0f;

		Window m_window;

		InputManager m_inputManager;


		bool init();
		bool initSystems();

		virtual void update();
		virtual void draw();

	};

}