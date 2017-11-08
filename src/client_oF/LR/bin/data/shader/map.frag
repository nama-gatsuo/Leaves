#version 400

uniform sampler2DRect tex0; // color image
uniform sampler2DRect tex1; // topography
uniform sampler2DRect tex2; // population
uniform sampler2DRect tex3; // gdp
uniform sampler2DRect tex4; // population-growth
uniform sampler2DRect tex5; // unmarried-rate
uniform sampler2DRect tex6; // suicide-rate
uniform sampler2DRect tex7; // aids
uniform sampler2DRect tex8; // cancer
uniform float p1;
uniform float p2;
uniform float p3;
uniform float p4;
uniform float p5;
uniform float p6;
uniform float p7;
uniform float p8;

in vec2 vTexCoord;
out vec4 outputColor1; // color
out vec4 outputColor2; // height

void main(){

    vec2 st = vTexCoord * 2.;

    // height
    float t = 0.;
    // coloring
    vec3 c = vec3(0.);
    vec3 col = vec3(0.);

    // topography
    c = texture(tex0, st).rgb;
    float grey = (c.r + c.g + c.b) / 3.;
    c = texture(tex1, st).rgb;
    col += grey * p1;
    t += (c.r * 0.02 + 0.03) * p1;

    // population
    c = texture(tex2, st).rgb;
    col += c * p2;
    t += c.r * p2 * 0.04;

    // gdp
    c = texture(tex3, st).rgb;
    col += c * p3;
    t += c.r * p3 * 0.04;

    // population-growth
    c = texture(tex4, st).rgb;
    col += (c.r * vec3(0.7, 0.2, 0.4) + c.b * vec3(0.05, 0.5, 0.8)) * p4;
    t -= c.r * p4 * 0.05;
    t += c.b * p4 * 0.05;

    // unmarried-rate
    c = texture(tex5, st).rgb;
    col += c * p5;
    t += c.r * p5 * 0.04;

    // suicide-rate
    c = texture(tex6, st).rgb;
    col += c * p6;
    t += c.r * p6 * 0.04;

    // aids
    c = texture(tex7, st).rgb;
    col += c * p7;
    t += c.r * p7 * 0.04;

    // cancer
    c = texture(tex8, st).rgb;
    col += c * p8;
    t += c.r * p8 * 0.04;

    outputColor1 = vec4(col, 1.);
    outputColor2 = vec4(vec3(t + 0.96), 1.);

}
