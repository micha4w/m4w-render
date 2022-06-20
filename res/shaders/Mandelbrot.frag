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


const float MAX_ITERATION = 100;
const float MAX_VALUE     = 1000;

#define product(a, b) vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x)

void main () {
    float i = 0;
    vec2 z = vec2(0);

    while ( i < MAX_ITERATION ) {
        z = product(z,z) + v_TexCoord;

        if ( z == vec2(0) ) {
            o_FragColor = vec4(0, 0, 0, 1);
            return;
        } else if ( z.x > MAX_VALUE || z.y > MAX_VALUE ) {
            o_FragColor = vec4(vec3(i / MAX_ITERATION), 1);
            return;
        }

        i++;
    }


    o_FragColor = vec4(1);
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