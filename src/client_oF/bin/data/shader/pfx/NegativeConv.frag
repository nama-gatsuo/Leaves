#version 410

uniform sampler2DRect tex0;
uniform float isNega;

in vec4 vColor;
in vec2 vTexCoord;
out vec4 outputColor;

void main() {

    // flip vertical
    vec2 st = vec2(textureSize(tex0).x - vTexCoord.x, vTexCoord.y);

    vec4 col = texture(tex0, st);
    if (isNega > 0.5) col.rgb = vec3(dot(vec3(1.0) - col.rgb, vec3(1.0)) / 3.0);

    outputColor = col;
}
