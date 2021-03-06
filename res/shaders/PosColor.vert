#version 330 core

layout( location = 0 ) in vec4 a_Position;
layout( location = 1 ) in vec4 a_Normal;
layout( location = 2 ) in vec4 a_Color;
layout( location = 3 ) in vec2 a_TexCoord;

uniform vec3 u_WorldPos;
uniform mat4 u_Model;
uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec4 v_WorldPos;

void main () {
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;

    v_WorldPos = u_Model * a_Position;
    v_Normal = (u_Model * a_Normal).xyz - u_WorldPos;

    gl_Position = u_MVP * a_Position;
}