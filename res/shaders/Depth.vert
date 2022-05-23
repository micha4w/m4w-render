#version 330 core

layout( location = 0 ) in vec3 a_Position;

uniform mat4 u_MVP;

out float v_Depth;

void main() {
    gl_Position = u_MVP * vec4(a_Position, 1.f);
}