#pragma once
#include <SDL3/SDL.h>

namespace rm {
    class Renderer {
    public:
        static void Init(SDL_Renderer* renderer);
        static void Shutdown();
        static SDL_Renderer* GetHandle();
        static SDL_GPUDevice* GetGPUDevice();

        static void Present(const SDL_FColor& clearColor = { 0.9f,0.9f,0.95f,1.0f });
    private:
        static void CreateGPUDevice();
        static void CreateShaders();
        static void CreateGraphicsPipeline();
        static void DestroyGraphicsPipeline();
        static void DestroyShaders();
        static void DestroyGPUDevice();
    };
} // namespace rm
