#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;
in vec2 texcoord;

uniform int last;
uniform float t;

out vec3 vColor;

const float PI = 3.14159265358979323;

void main() {

    vec4 p = position;
    float size = 1.0;

    vColor = color.rgb * size;

    gl_Position = modelViewProjectionMatrix * p;
    gl_PointSize = size * 400.0 / gl_Position.w;
}
