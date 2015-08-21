#ifndef TIMING_H_INCLUDED
#define TIMING_H_INCLUDED

namespace taengine {
    class FPSLimiter {
        public:
            FPSLimiter();

            void init(float maxFPS);

            void setMaxFPS(float maxFPS);

            void begin();
            // end will return current FPS
            float end();

        private:
            float m_fps;
            float m_frameTime;
            float m_maxFPS;
            unsigned int m_startTicks;

            void calculateFPS();

    };
}

#endif // TIMING_H_INCLUDED
