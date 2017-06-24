#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec3 vColor;

const float PI = 3.14159265358979323;

void main() {
    vColor = color.rgb;
    gl_Position = modelViewProjectionMatrix * position;
    gl_PointSize = 800.0 / gl_Position.w;
}
