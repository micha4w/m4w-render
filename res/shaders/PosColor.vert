#version 330 core

layout(location=0) in vec3 a_Position;
layout(location=1) in vec3 a_Normal;
layout(location=2) in vec4 a_Color;
layout(location=3) in vec2 a_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform sampler2D u_Texture;
uniform int u_TextureID;

out vec4 v_Color;

void main() {
    v_Color = a_Color + texture2D(u_Texture, a_TexCoord);// + vec4(0,0,.5,1);
    v_Color = vec4(a_TexCoord, 0, 1.);
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.f);
}