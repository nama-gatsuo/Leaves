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

    if (gl_VertexID == last) {
        if (t < 1.0) {
            p.xyz = p.xyz * (0.8 + 0.2 * t);
            size *= (5. - 4. * t);
        }
    }

    vColor = color.rgb * size;

    gl_Position = modelViewProjectionMatrix * p;
    gl_PointSize = size * 1200.0 / gl_Position.w;
}
