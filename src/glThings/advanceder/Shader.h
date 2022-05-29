#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "HeapArray.h"

namespace m4w {

    class Shader {

    private:
        unsigned int m_ID;

        std::string m_FragmentFile;
        std::string m_VertexFile;

        void Load (std::string path, unsigned int type) {
            std::ifstream input;
            input.open(path);
            
            std::string code;
            try {
                code = std::string( std::istreambuf_iterator<char>(input),
                                    std::istreambuf_iterator<char>(     ) );
                                    
            } catch (std::ifstream::failure fail) {
                std::cout << "[ERROR] Can't read file: res/shaders/" << path << "\n";
            }
            input.close();
    
            // Compile Shader
            unsigned int shader = glCreateShader(type);

            const char* rawCode = code.c_str();
            glShaderSource(shader, 1, &rawCode, NULL);
            glCompileShader(shader);

            // Debug compile Errors
            int success;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                char infoLog[512];
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "[ERROR] Shader compilation failed: " << std::filesystem::current_path() << path << "\n" << code << "\n" << rawCode << "\n" << infoLog << std::endl;

                glDeleteShader(shader);
                return;
            };

            // Link Shader
            glAttachShader(m_ID, shader);
            
            // Delete shader
            glDeleteShader(shader);
        }

        void Link() {
            glLinkProgram(m_ID);

            // Debug linking Errors
            int success;
            glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
            if(!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
                std::cout << "[ERROR] Shader linking failed!\n" << infoLog << "\n";
            }
        }

        std::map<std::string, int> m_UniformLocations;
        int GetUniformLocation (const char* name) {

            auto location = m_UniformLocations.find(name);

            if ( location == m_UniformLocations.end() ) {
                int newLocation = glGetUniformLocation(m_ID, name);
                if ( newLocation == -1 ) {
                    std::cout << "[Warning] Uniform " << name << " not found in shader " << m_VertexFile << "\n";
                }
                m_UniformLocations.insert(std::pair<std::string, int>(name, newLocation));
                return newLocation;
            } else {
                return location->second;
            }
        }

    public:
        Shader (std::string vertexPath, std::string fragmentPath);
        Shader (std::string name);
        ~Shader ();
        
        void Bind ();
        static void Unbind ();
        void Recompile();

        void SetUniform1i(const char* name, int i0);
        void SetUniform2i(const char* name, int i0, int i1);
        void SetUniform3i(const char* name, int i0, int i1, int i2);
        void SetUniform4i(const char* name, int i0, int i1, int i2, int i3);

        void SetUniform1f(const char* name, float f0);
        void SetUniform2f(const char* name, float f0, float f1);
        void SetUniform3f(const char* name, float f0, float f1, float f2);
        void SetUniform4f(const char* name, float f0, float f1, float f2, float f3);

        void SetUniformMat4(const char* name, glm::mat4 matrix);
        void SetUniformLights(m4w::HeapArray<struct LightSource>& lights);
    };

}