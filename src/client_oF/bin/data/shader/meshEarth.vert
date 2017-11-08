#version 400
uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

out vec4 vColor;

uniform sampler2DRect bumpMap;
uniform sampler2DRect colorMap;

void main(){
    vec3 p = position.xyz;
    p *= texture(bumpMap, texcoord * textureSize(bumpMap)).r;

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.);
    vColor = texture(colorMap, texcoord * textureSize(colorMap));

}
