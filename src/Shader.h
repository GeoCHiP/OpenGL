#pragma once

#include "glm/glm.hpp"

#include <string>
#include <tuple>
#include <unordered_map>

class Shader {
public:
    Shader();
    Shader(const std::string &filepath);
    ~Shader();

    void LoadShader(const std::string &filepath);

    std::tuple<std::string, std::string> ParseShader(const std::string &filepath);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string &source);

    void Bind() const;
    void Unbind() const;

    int GetUniformLocation(const std::string &name);

    void SetUniform1i(const std::string &name, int value);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform3f(const std::string &name, float v0, float v1, float v2);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string &name, glm::mat4 &matrix);

private:
    std::string m_File;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};