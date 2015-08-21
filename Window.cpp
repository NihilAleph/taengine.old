#include "Window.h"
#include "TaengineErrors.h"

#include <iostream>


namespace taengine {
    Window::Window()
    {
        //ctor
    }

    Window::~Window()
    {
        //dtor
    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

        Uint32 flags = SDL_WINDOW_OPENGL;

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

        if (currentFlags & INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
        }
        if (currentFlags & FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (currentFlags & BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
        }

        m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

        if (m_sdlWindow == nullptr) {
            fatalError("SDL Window could not be open!");
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
        if (glContext == nullptr) {
            fatalError("SDL_GL context could not be created!");
        }

        GLenum error = glewInit();
        if (error != GLEW_OK) {
            fatalError("Could not initialize glew!");
        }

        // checking openGL version
        std::cout<< "*** OpenGL Version: " << glGetString(GL_VERSION) << " ***" << std::endl;

        glClearColor(0.0f,0.0f,0.0f,1.0f);

        // VSYNC is on (1) or off (0)
        SDL_GL_SetSwapInterval(0);

        // enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;

    }


    void Window::swapBuffer() {
        // swap buffer of the window
        SDL_GL_SwapWindow(m_sdlWindow);
    }
}
