#include "Timing.h"
#include <SDL/SDL.h>

namespace taengine {

    FPSLimiter::FPSLimiter() {
    }

    void FPSLimiter::init(float maxFPS) {
        setMaxFPS(maxFPS);
    }

    void FPSLimiter::setMaxFPS(float maxFPS) {
        m_maxFPS = maxFPS;
    }

    void FPSLimiter::begin() {
        m_startTicks = SDL_GetTicks();
    }
    // end will return current FPS
    float FPSLimiter::end() {

        calculateFPS();

        float frameTicks = SDL_GetTicks() - m_startTicks;
        // limit FPS to maxFPS
        if (1000.0f/m_maxFPS > frameTicks) {
            SDL_Delay(1000.0f/m_maxFPS - frameTicks);
        }

        return m_fps;
    }


    void FPSLimiter::calculateFPS() {
        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;

        static float previousTicks = SDL_GetTicks();

        float currentTicks = SDL_GetTicks();

        m_frameTime = currentTicks - previousTicks;

        currentFrame++;
        previousTicks = currentTicks;

        frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

        int count;

        if (currentFrame < NUM_SAMPLES) {
            count = currentFrame;
        } else {
            count = NUM_SAMPLES;
        }

        float frameTimeAverage = 0;

        for (int i = 0;  i < count; i++) {
            frameTimeAverage += frameTimes[i];
        }

        frameTimeAverage /= count;

        if (frameTimeAverage > 0) {
            m_fps = 1000.0f / frameTimeAverage;
        } else {
            m_fps = 60.0f;
        }


    }


}
