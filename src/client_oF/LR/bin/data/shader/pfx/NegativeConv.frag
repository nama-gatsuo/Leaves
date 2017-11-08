#version 410

uniform sampler2DRect tex0;
uniform float isNega;

in vec4 vColor;
in vec2 vTexCoord;
out vec4 outputColor;

void main() {

    vec4 col = texture(tex0, vTexCoord);
    col.rgb = vec3(dot(vec3(1.0) - col.rgb, vec3(1.0)) / 3.0);

    outputColor = col;
}
