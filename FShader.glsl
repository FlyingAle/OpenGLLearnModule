#version 330 core
precision highp float;

out vec4 FragColor;
in vec3 ourColor;

in vec2 ourTexCoord;

uniform vec4 ourFColor;
uniform float opacityPercent;

uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
vec3 baseColor = texture2D(texture1,ourTexCoord).rgb;
vec3 coverColor = texture2D(texture2,ourTexCoord).rgb;
baseColor = mix(baseColor,coverColor,opacityPercent);
FragColor = vec4(baseColor,1.0);
}