#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D backgroundTexture;
uniform sampler2D foregroundTexture;

void main()
{
    vec4 bgColor = texture(backgroundTexture, TexCoord);
	vec4 fgColor = texture(foregroundTexture, TexCoord);

	color = mix(bgColor, vec4(1,1,1,1), fgColor.r);
}
