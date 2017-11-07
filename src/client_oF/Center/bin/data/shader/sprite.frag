#version 150

in vec3 vColor;
out vec4 outputColor;

void main() {

	vec3 n;
	n.xy = gl_PointCoord.xy * 2.0 - 1.0;
	float r2 = dot(n.xy, n.xy);
	n.z = 1.0 - r2;

	float pAlpha = smoothstep(0.0, 1., n.z);

 	if (pAlpha < 0.001) discard;
    outputColor = vec4(vColor / r2 * 0.2, pAlpha);
}
