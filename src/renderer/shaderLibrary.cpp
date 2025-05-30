#include "shaderLibrary.h"
#include <print>

namespace rm {

    void rm::ShaderLibrary::add(ref<Shader> shader) {
        std::filesystem::path name = shader->getPath().filename().replace_extension("");
        m_Library.try_emplace(name.string(), shader);
    }

    void ShaderLibrary::add(ref<Shader> shader, const std::string& name) {
        m_Library.try_emplace(name, shader);
    }

    ref<Shader> rm::ShaderLibrary::loadShader(const std::string& name) {
        if (!m_Library.contains(name))
            add(createRef<Shader>(name));

        return m_Library[name];
    }

    void ShaderLibrary::erase(const std::string& name) {
        m_Library.erase(name);
    }

    void ShaderLibrary::clear() {
        m_Library.clear();
    }

} // namespace rm