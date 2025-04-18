#pragma once
#include <SDL3/SDL.h>
#include <exception>
#include <filesystem>

namespace rm {

#ifndef SDL_Validate
#define SDL_Validate(condition) { \
        if (!condition) { \
            fprintf(stderr, "SDL Validation Failed!\n"); \
            fprintf(stderr, "  Condition: %s\n", #condition); \
            fprintf(stderr, "  SDL Error: %s\n", SDL_GetError()); \
            fprintf(stderr, "  Location: %s:%d\n", __FILE__, __LINE__); \
            abort();\
        }\
    }
#endif // SDL_Validate

} // namespace rm