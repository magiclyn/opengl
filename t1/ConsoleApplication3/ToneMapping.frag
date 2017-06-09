uniform sampler2D texSrc;
uniform sampler2D texBloom;
uniform float AveLum;
uniform float Key;
const vec4 lumfact = vec4(0.27,0.67,0.06,0.0);
void main()
{
	vec4 color = texture2D(texSrc,gl_TexCoord[0].xy);
	float lum = dot(color , lumfact);
    color *= Key *lum/AveLum;
    color /= vec4(vec4(1.0,1.0,1.0,0.0)+color);
    gl_FragColor = clamp(color + texture2D(texBloom,gl_TexCoord[0].xy)*1.3, 0.0,1.0);
}