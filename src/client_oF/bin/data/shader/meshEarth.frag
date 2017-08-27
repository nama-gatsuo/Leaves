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
    //float grey = (vColor.r + vColor.g + vColor.b)/3.;
    //outputColor = vec4(vec3(grey), 1.);
    outputColor = vColor;
}
