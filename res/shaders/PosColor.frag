#version 330 core

uniform sampler2D u_Texture;
uniform int u_TextureID;

in vec4 v_Color;
in vec2 v_TexCoord;

void main() {
    gl_FragColor = v_Color + texture2D(u_Texture, v_TexCoord);
    //gl_FragColor = vec4(v_TexCoord, 0, 1);
}