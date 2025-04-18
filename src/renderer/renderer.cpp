#include "renderer.h"
#include "core/application.h"
#include "utils/sdlUtils.h"

#include <vector>
#include <print>
#include "renderer/shaderLibrary.h"


struct DrawList {
};

namespace rm {

    struct RenderData {
        SDL_Renderer* handle = nullptr;
        SDL_GPUDevice* gpuDeviceHandle = nullptr;
        SDL_GPUGraphicsPipeline* pipeline = nullptr;

        ref<ShaderLibrary> shaders = nullptr;

        std::vector<DrawList> drawList;
    };

    static RenderData s_Data;

    void Renderer::Init(SDL_Renderer* renderer) {
        s_Data.handle = renderer;
        CreateGPUDevice();
        CreateShaders();
        CreateGraphicsPipeline();
    }

    void Renderer::Shutdown() {
        DestroyGraphicsPipeline();
        DestroyShaders();
        DestroyGPUDevice();
        SDL_DestroyRenderer(s_Data.handle);

    }

    SDL_Renderer* Renderer::GetHandle() {
        return s_Data.handle;
    }

    SDL_GPUDevice* Renderer::GetGPUDevice() {
        return s_Data.gpuDeviceHandle;
    }

    void Renderer::Present(const SDL_FColor& clearColor) {
        SDL_GPUCommandBuffer* commandBuffer{ SDL_AcquireGPUCommandBuffer(s_Data.gpuDeviceHandle) };
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
            SDL_GPURenderPass* renderPass{ SDL_BeginGPURenderPass(commandBuffer, colorTargets.data(), colorTargets.size(), nullptr) };
            SDL_BindGPUGraphicsPipeline(renderPass, s_Data.pipeline);

            //TODO: Draw all elements in drawList.
            SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

            SDL_EndGPURenderPass(renderPass);
        }

        SDL_Validate(SDL_SubmitGPUCommandBuffer(commandBuffer));

    }

    void Renderer::CreateGPUDevice() {
        s_Data.gpuDeviceHandle = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL, true, nullptr);
        SDL_Validate(s_Data.gpuDeviceHandle);
        SDL_Validate(SDL_ClaimWindowForGPUDevice(s_Data.gpuDeviceHandle, Application::Get()->getWindowHandle()));
    }

    void Renderer::CreateShaders() {
        s_Data.shaders = createRef<ShaderLibrary>();
        s_Data.shaders->add(createRef<Shader>("RawTriangle.vert"), "vertexShader");
        s_Data.shaders->add(createRef<Shader>("SolidColor.frag"), "fragmentShader");
    }

    void Renderer::CreateGraphicsPipeline() {
        SDL_GPUColorTargetDescription colorTargetDescription{};
        colorTargetDescription.format = SDL_GetGPUSwapchainTextureFormat(s_Data.gpuDeviceHandle, Application::Get()->getWindowHandle());
        std::vector<SDL_GPUColorTargetDescription> colorTargetDescriptions{ colorTargetDescription };

        SDL_GPUGraphicsPipelineTargetInfo targetInfo{};
        targetInfo.color_target_descriptions = colorTargetDescriptions.data();
        targetInfo.num_color_targets = colorTargetDescriptions.size();

        SDL_GPUGraphicsPipelineCreateInfo createInfo{};
        createInfo.target_info = targetInfo;
        createInfo.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;
        createInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
        createInfo.vertex_shader = s_Data.shaders->loadShader("vertexShader")->getHandle();
        createInfo.fragment_shader = s_Data.shaders->loadShader("fragmentShader")->getHandle();

        s_Data.pipeline = SDL_CreateGPUGraphicsPipeline(s_Data.gpuDeviceHandle, &createInfo);
        SDL_Validate(s_Data.pipeline);
    }

    void Renderer::DestroyGraphicsPipeline() {
        SDL_ReleaseGPUGraphicsPipeline(s_Data.gpuDeviceHandle, s_Data.pipeline);
    }

    void Renderer::DestroyShaders() {
        s_Data.shaders->clear();
    }

    void Renderer::DestroyGPUDevice() {
        SDL_ReleaseWindowFromGPUDevice(s_Data.gpuDeviceHandle, Application::Get()->getWindowHandle());
        SDL_DestroyGPUDevice(s_Data.gpuDeviceHandle);
    }


} // namespace rm
