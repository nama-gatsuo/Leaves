#version 400

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2DRect sea;
uniform sampler2DRect density;
uniform float denseParam;

out vec4 outputColor;

void main(){

    vec4 sc = texture(sea, vTexCoord * textureSize(sea));

    bool isSea = (sc.r + sc.g + sc.b) > 0.01;
    if (isSea) discard;

    vec4 c1 = vec4(0.1) + vec4((vColor.r+vColor.g+vColor.b)/3.) * 0.2 + vColor * 0.25;
    float d = texture(density, vTexCoord * textureSize(density)).r;
    vec4 c2 = vec4(vec3(0.7, 0.6, 0.5) * d, 1.);

    outputColor = mix(c1, c2, denseParam);
}
