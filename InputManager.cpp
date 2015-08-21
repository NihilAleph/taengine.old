#include "InputManager.h"

namespace taengine {
    InputManager::InputManager() : m_mouseCoords(0.0f, 0.0f)
    {
        //ctor
    }

    InputManager::~InputManager()
    {
        //dtor
    }

	void InputManager::update() {
		for (auto& it : m_keyMap) {
			m_previousKeyMap[it.first] = it.second;
		}
	}

    void InputManager::pressKey(unsigned int keyID) {

        // unsorted map can behave like arrays, using de index as key
        m_keyMap[keyID] = true;
    }
    void InputManager::releaseKey(unsigned int keyID) {
        m_keyMap[keyID] = false;
    }


	bool InputManager::isKeyUp(unsigned int keyID) {
		auto it = m_keyMap.find(keyID);
		// if key exists, return the value, otherwise return true
		if (it != m_keyMap.end())
			return !it->second;
		else return true;
	}


	bool InputManager::isKeyPressed(unsigned int keyID) {
		// Check if it is pressed this frame, and wasn't pressed last frame
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}
		return false;
	}

    bool InputManager::isKeyDown(unsigned int keyID) {
        auto it = m_keyMap.find(keyID);
        // if key exists, return the value, otherwise return false
        if (it != m_keyMap.end())
            return it->second;
        else return false;
    }


	bool InputManager::isKeyReleased(unsigned int keyID) {
		// Check if it is pressed this frame, and wasn't pressed last frame
		if (isKeyDown(keyID) == false && wasKeyDown(keyID) == true) {
			return true;
		}
		return false;
	}



    void InputManager::setMouseCoords(float x, float y) {
        m_mouseCoords.x = x;
        m_mouseCoords.y = y;
    }


	bool InputManager::wasKeyUp(unsigned int keyID) {
		auto it = m_previousKeyMap.find(keyID);
		// if key exists, return the value, otherwise return true
		if (it != m_previousKeyMap.end())
			return !it->second;
		else return true;
	}
	bool InputManager::wasKeyDown(unsigned int keyID) {

		auto it = m_previousKeyMap.find(keyID);
		// if key exists, return the value, otherwise return false
		if (it != m_previousKeyMap.end())
			return it->second;
		else return false;
	}
}
