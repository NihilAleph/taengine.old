#include "TaengineErrors.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include <SDL/SDL.h>

namespace taengine {
    void fatalError(std::string errorString) {
        std::cout << errorString << std::endl;
        std::cout << "Press any key to quit...";
        int tmp;
        std::cin >> tmp;

        SDL_Quit();
        exit(1);
    }
}
