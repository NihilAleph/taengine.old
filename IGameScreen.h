#pragma once
#define SCREEN_INDEX_NO_SCREEN -1

namespace taengine {

	class IMainGame;

	enum class ScreenState {
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};
	class IGameScreen
	{
	public:
		friend class ScreenList;
		IGameScreen() {
			// Empty
		}
		virtual ~IGameScreen() {
			// Empty
		}

		// Called at beggining and end of application
		// These virtual functions need to be overrided
		virtual void build() = 0;
		virtual void destroy() = 0;

		// Called when screen enters or exit focus
		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		// Called in the main game loop
		virtual void update() = 0;
		virtual void draw() = 0;

		int getScreenIndex() const {
			return m_screenIndex;
		}

		ScreenState getState() const {
			return m_currentState;
		}

		// Return the index of the next or previous screen when changing screens
		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		void setRunning() {
			m_currentState = ScreenState::RUNNING;
		}

		void setParentGame(IMainGame* game) {
			m_game = game;
		}
	protected:
		ScreenState m_currentState = ScreenState::NONE;
		IMainGame* m_game = nullptr;

		int m_screenIndex = -1;
	};



}