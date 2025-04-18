#pragma once
#include "shader.h"
#include <unordered_map>
#include <string>
#include "utils/base.h"

namespace rm {
    class ShaderLibrary {
    public:
        void add(ref<Shader> shader);
        void add(ref<Shader> shader, const std::string& name);
        ref<Shader> loadShader(const std::string& name);
    private:
        std::unordered_map<std::string,ref<Shader>> m_Library;
    };
} // namespace rm
