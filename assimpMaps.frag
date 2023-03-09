#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular2;

uniform float shininess;

uniform vec3 viewPos; 

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform PointLight pointLight;
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

struct SpotLight {
    vec3 position;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;
};  
uniform SpotLight spotLight;
vec3 CalcSpotLight(SpotLight light,vec3 normal, vec3 fragPos, vec3 viewDir);
void main()
{
  // ����
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // ��һ�׶Σ��������
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // �ڶ��׶Σ����Դ
     result += CalcPointLight(pointLight, norm, FragPos, viewDir);  
  // Ҳ���������Ĺ�Դ������۹⣩
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);  
    FragColor = vec4(result, 1.0);
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // �ϲ����
    vec3 ambient  = light.ambient  * vec3(mix(texture(texture_diffuse1, TexCoords), texture(texture_diffuse2, TexCoords), 0.0));
    vec3 diffuse  = light.diffuse  * diff * vec3(mix(texture(texture_diffuse1, TexCoords), texture(texture_diffuse2, TexCoords), 0.0));
    vec3 specular = light.specular * spec * vec3(mix(texture(texture_specular1, TexCoords), texture(texture_specular2, TexCoords), 0.0));
    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // ˥��
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // �ϲ����
    vec3 ambient  = light.ambient  * vec3(mix(texture(texture_diffuse1, TexCoords), texture(texture_diffuse2, TexCoords), 0.0));
    vec3 diffuse  = light.diffuse  * diff * vec3(mix(texture(texture_diffuse1, TexCoords), texture(texture_diffuse2, TexCoords), 0.0));
    vec3 specular = light.specular * spec * vec3(mix(texture(texture_specular1, TexCoords), texture(texture_specular2, TexCoords), 0.0));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light,vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient  = light.ambient  * vec3(mix(texture(texture_diffuse1, TexCoords), texture(texture_diffuse2, TexCoords), 0.0));
    vec3 diffuse  = light.diffuse  * diff * vec3(mix(texture(texture_diffuse1, TexCoords), texture(texture_diffuse2, TexCoords), 0.0));
    vec3 specular = light.specular * spec * vec3(mix(texture(texture_specular1, TexCoords), texture(texture_specular2, TexCoords), 0.0));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}