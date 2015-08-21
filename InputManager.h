#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace taengine {
    class InputManager
    {
        public:
            InputManager();
            virtual ~InputManager();

			void update();

            void pressKey(unsigned int keyID);
            void releaseKey(unsigned int keyID);

			bool isKeyUp(unsigned int keyID);
			bool isKeyPressed(unsigned int keyID);
			bool isKeyDown(unsigned int keyID);
			bool isKeyReleased(unsigned int keyID);

            void setMouseCoords(float x, float y);
            // this function does not change the state of the object
            glm::vec2 getMouseCoords() const { return m_mouseCoords; }

        protected:
        private:
            // unsorted map = hashmap
			std::unordered_map<unsigned int, bool> m_keyMap;
			std::unordered_map<unsigned int, bool> m_previousKeyMap;
            glm::vec2 m_mouseCoords;


			bool wasKeyUp(unsigned int keyID);
			bool wasKeyDown(unsigned int keyID);
    };
}
#endif // INPUTMANAGER_H
