#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace taengine {
    enum WindowFlag { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

    class Window
    {
        public:
            Window();
            virtual ~Window();

            int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

            int getScreenWidth() { return m_screenWidth; };
            int getScreenHeight() { return m_screenHeight; };

            void swapBuffer();
        protected:
        private:
            SDL_Window* m_sdlWindow;
            int m_screenWidth;
            int m_screenHeight;
    };
}

#endif // WINDOW_H
