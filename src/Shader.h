#pragma once

#include "glm/glm.hpp"

#include <string>
#include <tuple>
#include <unordered_map>

class Shader {
public:
    Shader(const std::string &filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string &name, int value);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform2f(const std::string &name, const glm::vec2 &value);
    void SetUniform3f(const std::string &name, const glm::vec3 &value);
    void SetUniform4f(const std::string &name, const glm::vec4 &value);
    void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

private:
    std::tuple<std::string, std::string> ParseShader(const std::string &filepath);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    int GetUniformLocation(const std::string &name) const;

private:
    std::string m_File;
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};