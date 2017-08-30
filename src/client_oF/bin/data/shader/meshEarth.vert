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
out float vIsSea;

uniform sampler2DRect sea;

// 0: topography, 1: population-density, 2: gdp-per-capita
// 3: population-growth, 4: unmarried-rate, 5: suicide-rate
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform sampler2DRect tex3;
uniform sampler2DRect tex4;
uniform sampler2DRect tex5;
uniform float p0;
uniform float p1;
uniform float p2;
uniform float p3;
uniform float p4;
uniform float p5;

void main(){
    vec3 p = position.xyz;

    vec4 sc = texture(sea, texcoord * textureSize(sea));
    bool isSea = (sc.r + sc.g + sc.b) > 0.01;
    vIsSea = isSea ? 1. : 0.;

    // height
    float t = 0.;
    // coloring
    vec3 c = vec3(0.);
    vec3 col = vec3(0.);

    c = texture(tex0, texcoord * textureSize(tex0)).rgb;
    col += (color.rgb + vec3(0.4)) * p0 * 0.3;
    t += c.r * p0 * 0.02;

    c = texture(tex1, texcoord * textureSize(tex1)).rgb;
    col += c * p1;
    t += c.r * p1 * 0.1;

    c = texture(tex2, texcoord * textureSize(tex2)).rgb;
    col += c * p2;
    t += c.r * p2 * 0.1;

    c = texture(tex3, texcoord * textureSize(tex3)).rgb;
    col += c * p3;
    t -= c.r * p3 * 0.1;
    t += c.b * p3 * 0.1;

    c = texture(tex4, texcoord * textureSize(tex4)).rgb;
    col += c * p4;
    t += c.r * p4 * 0.1;

    c = texture(tex5, texcoord * textureSize(tex5)).rgb;
    col += c * p5;
    t += c.r * p5 * 0.1;

    p *= 0.95 + t;

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.);
    // vTexCoord = texcoord;

    vColor = vec4(col * 0.8, 1.0);

}
