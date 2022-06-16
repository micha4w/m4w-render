#version 330 core

#define PI_2 6.2831853076
#define PI_7D4 5.49778714415
#define PI_3D2 4.7123889807
#define PI_5D4 3.92699081725
#define PI 3.1415926538
#define PI_3D4 2.35619449035
#define PI_D2 1.5707963269
#define PI_D4 0.78539816345


struct LightSource {
    vec3 PosOrDir;
    float Strength;
    vec3 Hue;

    float FOV; // As radians
    vec2 Size;
    mat4 VP;

    vec2 Offset;
};

const int PERSPECTIVE = 0;
const int ORTHOGRAPHIC = 1;
const int NO_TEXTURE = 2;

// Mesh stuff
uniform sampler2D u_Texture;
uniform int u_Toggle;

// Lighting stuff
uniform int u_LightCount;
uniform LightSource[32] u_Lights;
uniform sampler2D u_LightTexture;
uniform vec2 u_LightSize;
uniform float u_LightFactor;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec4 v_WorldPos;

out vec4 o_FragColor;

const vec3 base_light = vec3( 0.2, 0.25, 0.3 );

float clamp0to1 (float x) {
    return x/1+x;
}


void main () {

    vec3 ambient_darkness = vec3( 1.f );
    
    for ( int i = 0 ; i < u_LightCount ; i++ ) {

        vec4 uv_coord = u_Lights[i].VP * v_WorldPos * 0.5 + 0.5;
        vec3 posToLight = mix( -u_Lights[i].PosOrDir, u_Lights[i].PosOrDir - v_WorldPos.xyz, vec3(u_Lights[i].FOV > 0) );
        float angleToLight = acos(dot(v_Normal, posToLight));
        float intensity;

        if ( 0 < uv_coord.x && uv_coord.x < 1 && 0 < uv_coord.y && uv_coord.y < 1 && u_Lights[i].FOV >= 0 ) {
            
            float center = texture2D(u_LightTexture, (uv_coord.xy + vec2(0, 0)) * u_LightFactor + u_Lights[i].Offset).r;
            float top =    texture2D(u_LightTexture, (uv_coord.xy + vec2(0,  1/u_LightSize.y)) * u_LightFactor + u_Lights[i].Offset).r;
            float bottom = texture2D(u_LightTexture, (uv_coord.xy + vec2(0, -1/u_LightSize.y)) * u_LightFactor + u_Lights[i].Offset).r;
            float left =   texture2D(u_LightTexture, (uv_coord.xy + vec2( 1/u_LightSize.x, 0)) * u_LightFactor + u_Lights[i].Offset).r;
            float right =  texture2D(u_LightTexture, (uv_coord.xy + vec2(-1/u_LightSize.x, 0)) * u_LightFactor + u_Lights[i].Offset).r;

            float closest_distance = min(center, min(top, min(bottom, min(left, right))));

            intensity = 1-6*(uv_coord.z - closest_distance);
        } else {
            intensity = ( dot( posToLight, v_Normal ) / ( length(posToLight) * length(v_Normal) ) );
        }

        ambient_darkness *= 1. - clamp((intensity  * 0.5 + 0.5) * u_Lights[i].Strength, 0., 1.) * u_Lights[i].Hue;
    }

    vec4 base_color = v_Color + texture2D(u_Texture, v_TexCoord);
    o_FragColor = vec4(base_color.rgb  * ( ( 1. - ambient_darkness ) * ( 1 - base_light ) + base_light ), base_color.a);
}



        // // Finding pixelsize
        // float pixelSize;
        // if ( u_Lights[i].FOV > 0 ) {
        //     // Pers
        //     pixelSize = tan(angleToLight / 2.) * uv_coord.z * 2. / min(u_LightSize.x, u_LightSize.y);

        // } else {
        //     // Ortho
        //     float pixelSizeX = u_Lights[i].Size.x / u_LightSize.x;
        //     float pixelSizeY = u_Lights[i].Size.y / u_LightSize.y;

        //     pixelSize = max(pixelSizeX, pixelSizeY);
        // }

        // float shadowPlay = tan(angleToLight) * pixelSize / 2;