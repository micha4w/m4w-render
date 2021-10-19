#include "Shader.h"

Shader::Shader (std::string vertexPath, std::string fragmentPath) 
    : m_FragmentFile(fragmentPath), m_VertexFile(vertexPath)
{
    m_ID = glCreateProgram();
    Load(vertexPath, GL_VERTEX_SHADER);
    Load(fragmentPath, GL_FRAGMENT_SHADER);
    Link();

    this->Bind();
}

Shader::Shader (std::string name)
    : Shader("res/shaders/" + std::string(name) + ".vert", "res/shaders/" + std::string(name) + ".frag")
{ }

Shader::~Shader() {
    this->Unbind();
    glDeleteProgram(m_ID);
}

void Shader::Bind() {
    glUseProgram(m_ID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::Recompile() {
    this->Unbind();
    glDeleteProgram(m_ID);

    m_ID = glCreateProgram();
    Load(m_VertexFile, GL_VERTEX_SHADER);
    Load(m_FragmentFile, GL_FRAGMENT_SHADER);
    Link();

    this->Bind();
}


void Shader::SetUniform1i(const char* name, int i0) {
    this->Bind();
    glUniform1i(GetUniformLocation(name), i0);
}

void Shader::SetUniform2i(const char* name, int i0, int i1) {
    this->Bind();
    glUniform2i(GetUniformLocation(name), i0, i1);
}

void Shader::SetUniform3i(const char* name, int i0, int i1, int i2) {
    this->Bind();
    glUniform3i(GetUniformLocation(name), i0, i1, i2);
}

void Shader::SetUniform4i(const char* name, int i0, int i1, int i2, int i3) {
    this->Bind();
    glUniform4i(GetUniformLocation(name), i0, i1, i2, i3);
}

void Shader::SetUniform1f(const char* name, float f0) {
    this->Bind();
    glUniform1f(GetUniformLocation(name), f0);
}

void Shader::SetUniform2f(const char* name, float f0, float f1) {
    this->Bind();
    glUniform2f(GetUniformLocation(name), f0, f1);
}

void Shader::SetUniform3f(const char* name, float f0, float f1, float f2) {
    this->Bind();
    glUniform3f(GetUniformLocation(name), f0, f1, f2);
}

void Shader::SetUniform4f(const char* name, float f0, float f1, float f2, float f3) {
    this->Bind();
    glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void Shader::SetUniformMat4(const char* name, glm::mat4 matrix) {
    this->Bind();
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, &matrix[0][0]);
}

