#pragma once

#include <string>
#include <tuple>
#include <unordered_map>

class Shader {
public:
    Shader(const std::string &filepath);
    ~Shader();

    std::tuple<std::string, std::string> ParseShader(const std::string &filepath);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string &source);

    void Bind() const;
    void Unbind() const;

    int GetUniformLocation(const std::string &name);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

private:
    std::string m_File;
    unsigned int m_RendererID;
    std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
};