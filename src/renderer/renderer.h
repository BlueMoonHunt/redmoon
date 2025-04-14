#pragma once
#include <SDL3/SDL.h>

namespace rm {
    class Renderer {
    public:
        static void Init(SDL_Renderer* renderer);
        static void Shutdown();
        static SDL_Renderer* getHandle();

        static void BeginFrame(const SDL_FColor& clearColor = { 0.9f,0.9f,0.95f,1.0f });
        static void EndFrame();
    private:
        static void createGPUDevice();
        static void createShaders();
        static void destroyShaders();
        static void destroyGPUDevice();
    };
} // namespace rm
