#include "renderer.h"
#include "core/application.h"
#include "utils/sdlUtils.h"

#include <vector>

struct RenderData {
    SDL_Renderer* handle = nullptr;
    SDL_GPUDevice* gpuDeviceHandle = nullptr;
    SDL_GPUShader* vertexShader = nullptr;
    SDL_GPUShader* fragmentShader = nullptr;
};

static RenderData s_Data;

namespace rm {
    void Renderer::Init(SDL_Renderer* renderer) {
        s_Data.handle = renderer;
        createGPUDevice();
        createShaders();
    }

    void Renderer::Shutdown() {
        destroyShaders();
        destroyGPUDevice();
        SDL_DestroyRenderer(s_Data.handle);
    }

    SDL_Renderer* Renderer::getHandle() {
        return s_Data.handle;
    }

    void Renderer::BeginFrame(const SDL_FColor& clearColor) {
        SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(s_Data.gpuDeviceHandle);
        SDL_Validate(commandBuffer);

        SDL_GPUTexture* swapchainTexture = nullptr;
        SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, Application::Get()->getWindowHandle(), &swapchainTexture, nullptr, nullptr);
        if (swapchainTexture) {
            SDL_GPUColorTargetInfo colorTargetInfo{};
            colorTargetInfo.texture = swapchainTexture;
            colorTargetInfo.clear_color = clearColor;
            colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
            colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

            std::vector<SDL_GPUColorTargetInfo> colorTargets{ colorTargetInfo };
            SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, colorTargets.data(), colorTargets.size(), nullptr);
            SDL_EndGPURenderPass(renderPass);
        }

        SDL_Validate(SDL_SubmitGPUCommandBuffer(commandBuffer));

    }

    void Renderer::EndFrame() {
    }

    void Renderer::createGPUDevice() {
        s_Data.gpuDeviceHandle = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL, true, nullptr);
        SDL_Validate(s_Data.gpuDeviceHandle);
        SDL_Validate(SDL_ClaimWindowForGPUDevice(s_Data.gpuDeviceHandle, Application::Get()->getWindowHandle()));
    }

    void Renderer::createShaders() {
        s_Data.vertexShader = SDL_LoadShader(s_Data.gpuDeviceHandle, "RawTriangle.vert", 0, 0, 0, 0);
        SDL_Validate(s_Data.vertexShader);
        s_Data.fragmentShader = SDL_LoadShader(s_Data.gpuDeviceHandle, "SolidColor.frag", 0, 0, 0, 0);
        SDL_Validate(s_Data.fragmentShader);
    }

    void Renderer::destroyShaders() {
        SDL_ReleaseGPUShader(s_Data.gpuDeviceHandle, s_Data.vertexShader);
        SDL_ReleaseGPUShader(s_Data.gpuDeviceHandle, s_Data.fragmentShader);
    }

    void Renderer::destroyGPUDevice() {
        SDL_ReleaseWindowFromGPUDevice(s_Data.gpuDeviceHandle, Application::Get()->getWindowHandle());
        SDL_DestroyGPUDevice(s_Data.gpuDeviceHandle);
    }


} // namespace rm
