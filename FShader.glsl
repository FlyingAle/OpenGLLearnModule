#version 330 core
precision highp float;

out vec4 FragColor;
in vec3 ourColor;

in vec2 ourTexCoord;
in vec3 Normal;
in vec3 outFragPos;

uniform vec4 ourFColor;
uniform float opacityPercent;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightPos;
uniform vec3 lightColor;


void main()
{
    //环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;



    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - outFragPos);

    float diff = max(dot(norm,lightDir),0.0);//对法向量与光源位置进行点乘
    vec3 diffuse = diff * lightColor;


	//最终光照效果
	vec3 resultLightColor = ambient + diffuse;


    vec3 baseColor = texture2D(texture1,ourTexCoord).rgb;
    vec3 coverColor = texture2D(texture2,ourTexCoord).rgb;
    baseColor = mix(baseColor,coverColor,opacityPercent);
    FragColor = vec4(baseColor,1.0);
}