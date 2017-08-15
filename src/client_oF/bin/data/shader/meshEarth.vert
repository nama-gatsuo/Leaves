#version 400
uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

out vec2 vTexCoord;
out vec4 vColor;

uniform sampler2DRect topo;
uniform float topoParam;
uniform sampler2DRect density;
uniform float denseParam;

void main(){
    vec3 p = position.xyz;
    float h = texture(topo, texcoord * textureSize(topo)).r * topoParam;
    p *= (1. + h * 200. / 6000.);

    float d = texture(density, texcoord * textureSize(density)).r * denseParam;
    p *= (1. - denseParam * 0.1 + d * 0.2);

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.);
    vTexCoord = texcoord;
    vColor = color;

}
