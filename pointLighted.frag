#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissionMap;
    float shininess;
};
uniform Material material;

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

uniform vec3 viewPos; 

void main()
{

//vec3 emissionMap = texture(material.emissionMap,TexCoord).rgb;

    vec3 ambient = texture(material.diffuse,TexCoord).rgb * light.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse,TexCoord).rgb * light.diffuse * diff;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular,TexCoord).rgb  * light.specular * spec;
    // pointLight
     float distance    = length(light.position - FragPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
     diffuse  *= attenuation;
     specular *= attenuation;
        
    vec3 result = (ambient + diffuse + specular )*light.color ;
    FragColor = vec4(result, 1.0);
}