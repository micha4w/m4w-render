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

mat3 inverse (mat3 matrix);

void main () {
    vec4 base_color = v_Color + texture2D(u_Texture, v_TexCoord);
    vec4 pos_from_light = u_LightVP * v_WorldPos;
    float frag_distance = pos_from_light.z * 0.5 + 0.5;
    float closest_distance = texture2D(u_Light, pos_from_light.xy * 0.5 + 0.5).r;
    
    vec3 lightDir = inverse(mat3(u_LightVP)) * vec3(0, 0, 1);
    bool has_shadow = closest_distance > frag_distance - max(0.05 * (1.0 - dot(v_Normal, lightDir)), 0.005);

    base_color = vec4(has_shadow, 0, 0, 1);

    vec3 ambient_darkness = vec3( 1.f );
    for ( int i = 0 ; i < u_LightCount ; i++ ) {
        vec3 vecToLight = u_Lights[i].Pos - v_WorldPos.xyz;
        float intensity = ( dot( vecToLight, v_Normal ) / ( length(vecToLight) * length(v_Normal) ) );
        ambient_darkness *= 1. - clamp((intensity  * 0.5 + 0.5) * u_Lights[i].Strength, 0., 1.) * u_Lights[i].Hue;
    }

    gl_FragColor = vec4(base_color.rgb  * ( ( 1. - ambient_darkness ) * ( 1 - base_light ) + base_light ), base_color.a);
}

float det(mat2 matrix) {
    return matrix[0].x * matrix[1].y - matrix[0].y * matrix[1].x;
}

mat3 inverse (mat3 matrix) {
    vec3 row0 = matrix[0];
    vec3 row1 = matrix[1];
    vec3 row2 = matrix[2];

    vec3 minors0 = vec3(
        det(mat2(row1.y, row1.z, row2.y, row2.z)),
        det(mat2(row1.z, row1.x, row2.z, row2.x)),
        det(mat2(row1.x, row1.y, row2.x, row2.y))
    );
    vec3 minors1 = vec3(
        det(mat2(row2.y, row2.z, row0.y, row0.z)),
        det(mat2(row2.z, row2.x, row0.z, row0.x)),
        det(mat2(row2.x, row2.y, row0.x, row0.y))
    );
    vec3 minors2 = vec3(
        det(mat2(row0.y, row0.z, row1.y, row1.z)),
        det(mat2(row0.z, row0.x, row1.z, row1.x)),
        det(mat2(row0.x, row0.y, row1.x, row1.y))
    );

    mat3 adj = transpose(mat3(minors0, minors1, minors2));

    return (1.0 / dot(row0, minors0)) * adj;
}