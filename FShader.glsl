#version 330 core
precision highp float;
//材质结构体
struct Material {
    //使用漫反射贴图实现环境光与漫反射光
    sampler2D diffuse;
    //镜面光照 使用镜面光贴图实现镜面光效果
    sampler2D specular;
    //反光度
    float shininess;
};
//聚光光源
struct SpotLight {

    //如果使用定向光 就不需要知道光源的位置了
    vec3 position;

    //定向光照射方向 , 聚光光源照射方向
     vec3 direction;



    vec3 ambient;
    vec3 diffuse;
    vec3 specular;


    //以下为实现点光源衰减所用的常数项

    float constant;
    //控制近距离衰减所用的一次项
    float linear;
    //控制远距离衰减所用的二次项
    float quadratic;


    //聚光光源夹角值
    float cutOff;
	//外光切
	float outerCutOff;
};
//定向光
struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//点光源
struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


#define NR_POINR_LIGHTS 4
uniform PointLight pointLights[NR_POINR_LIGHTS];


out vec4 FragColor;
in vec3 ourColor;

in vec2 ourTexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 ourFColor; 
uniform float opacityPercent;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;

//材质
uniform Material material;
//光照设置
uniform SpotLight light;

uniform DirLight dirLight;

vec3 CalcDirLight(DirLight dirLight,vec3 normal, vec3 viewDir);

vec3 CalcPointLight(PointLight pointLight,vec3 normal,vec3 fragPos,vec3 viewDir);

vec3 CalcSpotLight(SpotLight spotLight,vec3 normal,vec3 fragPos,vec3 viewDir);




void main()
{

    vec3 baseColor = texture2D(texture1,ourTexCoord).rgb;
    vec3 coverColor = texture2D(texture2,ourTexCoord).rgb;
    baseColor = mix(baseColor,coverColor,opacityPercent);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight,norm,viewDir);

    for(int i = 0; i < NR_POINR_LIGHTS;i++)
        //result += CalcPointLight(pointLights[i],norm,FragPos,viewDir);

    result += CalcSpotLight(light,norm,FragPos,viewDir);

    baseColor = mix(baseColor,result,0.3);

    FragColor = vec4(baseColor,1.0);
}


// 定向光计算
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
    //镜面光着色
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //合并结果
    vec3 ambient = light.ambient *  vec3(texture(material.diffuse,ourTexCoord));

    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,ourTexCoord));

    vec3 specular = light.specular * spec * vec3(texture(material.specular,ourTexCoord));

    return (ambient + diffuse + specular);
}
//点光源计算
vec3 CalcPointLight(PointLight pointLight,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
    //镜面光着色
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //结果合并
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,ourTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,ourTexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular,ourTexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight spotLight,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir = normalize(spotLight.position - fragPos);
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
    //镜面光着色
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //衰减
    float distance = length(spotLight.position - fragPos);
    float attenuation = 1.0/(spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
    //判断光照夹角
    float theta = dot(lightDir , normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) /epsilon ,0.0,1.0);
    //结果合并
    vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse,ourTexCoord));
    vec3 diffuse  = spotLight.diffuse * diff * vec3(texture(material.diffuse,ourTexCoord));
    vec3 specular = spotLight.specular * spec * vec3(texture(material.specular,ourTexCoord));

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}
