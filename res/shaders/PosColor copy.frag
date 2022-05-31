#version 330 core

struct LightSource {
    vec3 Pos;
    float Strength;
    vec3 Hue;
};

uniform sampler2D u_Texture;
uniform int u_TextureID;
uniform int u_LightCount;
uniform LightSource[100] u_Lights;
uniform mat4 u_LightVP;
uniform sampler2D u_Light;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec4 v_WorldPos;


const vec3 base_light = vec3( 0.2, 0.25, 0.3 );

void main () {
    vec4 base_color = v_Color + texture2D(u_Texture, v_TexCoord);

    vec3 ambient_darkness = vec3( 1.f );
    for ( int i = 0 ; i < u_LightCount ; i++ ) {
        vec3 vecToLight = u_Lights[i].Pos - v_WorldPos.xyz;
        float intensity = ( dot( vecToLight, v_Normal ) / ( length(vecToLight) * length(v_Normal) ) );
        ambient_darkness *= 1. - clamp((intensity  * 0.5 + 0.5) * u_Lights[i].Strength, 0., 1.) * u_Lights[i].Hue;
    }

    gl_FragColor = vec4(base_color.rgb  * ( ( 1. - ambient_darkness ) * ( 1 - base_light ) + base_light ), base_color.a);
}