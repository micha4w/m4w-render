#include "Shader.h"

#include <iostream>

#include "Light.h"
#include "HeapArray.h"
#include "Context.h"

m4w::Shader::Shader (std::string vertexPath, std::string fragmentPath) 
    : m_FragmentFile(fragmentPath), m_VertexFile(vertexPath)
{
    m_ID = glCreateProgram();
    Load(vertexPath, GL_VERTEX_SHADER);
    Load(fragmentPath, GL_FRAGMENT_SHADER);
    Link();

    this->Bind();
}

m4w::Shader::Shader (std::string name)
    : Shader("res/shaders/" + std::string(name) + ".vert", "res/shaders/" + std::string(name) + ".frag")
{ }

m4w::Shader::~Shader () {
    this->Unbind();
    glDeleteProgram(m_ID);
}

void m4w::Shader::Bind () {
    glUseProgram(m_ID);
}

void m4w::Shader::Unbind () {
    glUseProgram(0);
}

void m4w::Shader::Recompile () {
    this->Unbind();
    glDeleteProgram(m_ID);
    m_UniformLocations.clear();

    m_ID = glCreateProgram();
    Load(m_VertexFile, GL_VERTEX_SHADER);
    Load(m_FragmentFile, GL_FRAGMENT_SHADER);
    Link();

    this->Bind();
}


void m4w::Shader::SetUniform1i (const char* name, int i0) {
    this->Bind();
    glUniform1i(GetUniformLocation(name), i0);
}

void m4w::Shader::SetUniform2i (const char* name, int i0, int i1) {
    this->Bind();
    glUniform2i(GetUniformLocation(name), i0, i1);
}

void m4w::Shader::SetUniform3i (const char* name, int i0, int i1, int i2) {
    this->Bind();
    glUniform3i(GetUniformLocation(name), i0, i1, i2);
}

void m4w::Shader::SetUniform4i (const char* name, int i0, int i1, int i2, int i3) {
    this->Bind();
    glUniform4i(GetUniformLocation(name), i0, i1, i2, i3);
}

void m4w::Shader::SetUniform1f (const char* name, float f0) {
    this->Bind();
    glUniform1f(GetUniformLocation(name), f0);
}

void m4w::Shader::SetUniform2f (const char* name, float f0, float f1) {
    this->Bind();
    glUniform2f(GetUniformLocation(name), f0, f1);
}

void m4w::Shader::SetUniform3f (const char* name, float f0, float f1, float f2) {
    this->Bind();
    glUniform3f(GetUniformLocation(name), f0, f1, f2);
}

void m4w::Shader::SetUniform4f (const char* name, float f0, float f1, float f2, float f3) {
    this->Bind();
    glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void m4w::Shader::SetUniformMat4 (const char* name, glm::mat4 matrix) {
    this->Bind();
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, &matrix[0][0]);
}

void m4w::Shader::SetUniformLights () {

    this->SetUniform1i("u_LightCount", g_Context.m_Lights.GetSize());
    int d = g_Context.m_LightHandler->GetDimensions();
    this->SetUniform1f("u_LightFactor", 1.f / d);
    this->SetUniform2f("u_LightSize", g_Context.m_LightHandler->GetFrameBuffer()->GetWidth() / d, g_Context.m_LightHandler->GetFrameBuffer()->GetHeight() / d);
    g_Context.m_LightHandler->GetFrameBuffer()->GetDepthBuffer()->Use(*this, 1, "u_LightTexture");

    unsigned int i = 0;
    for ( auto& [id, light] : g_Context.m_Lights ) {


        glm::vec3 posOrDir = light.m_Camera->GetProjectionType() == Perspective ? light.m_Camera->GetPosition() : light.m_Camera->GetOffset();
        this->SetUniform3f((std::string("u_Lights[") + std::to_string(i) + "].PosOrDir").c_str(), posOrDir.x, posOrDir.y, posOrDir.z);
        this->SetUniform1f((std::string("u_Lights[") + std::to_string(i) + "].Strength").c_str(), light.m_Strength);
        this->SetUniform3f((std::string("u_Lights[") + std::to_string(i) + "].Hue").c_str(), light.m_Hue[0], light.m_Hue[1], light.m_Hue[2]);
        
        switch ( light.m_Camera->GetProjectionType() ) {
        case Perspective:
            this->SetUniform1f((std::string("u_Lights[") + std::to_string(i) + "].FOV").c_str(), light.m_Camera->GetFOV().GetRadians());
            break;
        
        case Orthographic:
            this->SetUniform1f((std::string("u_Lights[") + std::to_string(i) + "].FOV").c_str(), 0.f);
            this->SetUniform2f((std::string("u_Lights[") + std::to_string(i) + "].Size").c_str(), light.m_Camera->GetWidth(), light.m_Camera->GetHeight());
            break;

        default:
            this->SetUniform1f((std::string("u_Lights[") + std::to_string(i) + "].FOV").c_str(), -1.f);
            break;
        }
        

        this->SetUniformMat4((std::string("u_Lights[") + std::to_string(i) + "].VP").c_str(), light.m_Camera->GetMatrix());

        this->SetUniform2f((std::string("u_Lights[") + std::to_string(i) + "].Offset").c_str(), light.GetTexturePos() / d / (float) d, light.GetTexturePos() % d / (float) d);

        i++;
    }
}
