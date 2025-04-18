#include "shader.h"
#include "renderer/renderer.h"

#include <fstream>
#include "utils/sdlUtils.h"
#include <vector>
#include "assetManager/assetManager.h"

namespace rm {
    Shader::Shader(const std::filesystem::path& shaderFilename, uint32_t samplerCount, uint32_t uniformBufferCount, uint32_t storageBufferCount, uint32_t storageTextureCount) {
        SDL_GPUDevice* device = Renderer::GetGPUDevice();
        SDL_GPUShaderStage stage;
        if (shaderFilename.extension() == ".vert")
            stage = SDL_GPU_SHADERSTAGE_VERTEX;
        else if (shaderFilename.extension() == ".frag")
            stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
        else {
            SDL_Log("Invalid shader stage!");
            abort();
        }

        const std::filesystem::path s_BasePath = AssetManager::GetBasePath();
        m_Path = s_BasePath / "res/Shaders/Compiled";

        SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
        const char* entrypoint;

        SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(device);
        if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
            m_Path /= "SPIRV" / shaderFilename;
            m_Path.concat(".spv");
            format = SDL_GPU_SHADERFORMAT_SPIRV;
            entrypoint = "main";
        }
        else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL) {
            m_Path /= "MSL" / shaderFilename;
            m_Path.concat(".msl");
            format = SDL_GPU_SHADERFORMAT_MSL;
            entrypoint = "main0";
        }
        else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) {
            m_Path /= "DXIL" / shaderFilename;
            m_Path.concat(".dxil");
            format = SDL_GPU_SHADERFORMAT_DXIL;
            entrypoint = "main";
        }
        else {
            SDL_Log("%s", "Unrecognized backend shader format!");
            abort();
        }

        std::ifstream file{ m_Path, std::ios::binary };
        SDL_Validate(file);
        std::string contents{ std::istreambuf_iterator(file), {} };
        std::vector<Uint8> code(contents.begin(), contents.end());


        SDL_GPUShaderCreateInfo shaderInfo{};

        shaderInfo.code = code.data();
        shaderInfo.code_size = code.size();
        shaderInfo.entrypoint = entrypoint;
        shaderInfo.format = format;
        shaderInfo.stage = stage;
        shaderInfo.num_samplers = samplerCount;
        shaderInfo.num_uniform_buffers = uniformBufferCount;
        shaderInfo.num_storage_buffers = storageBufferCount;
        shaderInfo.num_storage_textures = storageTextureCount;

        m_handle = SDL_CreateGPUShader(device, &shaderInfo);
        SDL_Validate(m_handle);
    }
    Shader::~Shader() {
        SDL_ReleaseGPUShader(Renderer::GetGPUDevice(), m_handle);
    }
    SDL_GPUShader* Shader::getHandle() {
        return m_handle;
    }
} // namespace rm