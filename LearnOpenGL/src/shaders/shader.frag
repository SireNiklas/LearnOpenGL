#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position; // Position for a "Point Light"
    vec3 direction; // Position no longer needed for a "Directional Light"

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

in vec2 TexCoords;

uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos); // Normalized to unit vectors and got the direction vector

    // Light calc
    // Ambiance
    //float ambientStrength = 0.1f;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // Normals
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(-light.direction); // Direction Light
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // Spotlight softedges
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // Attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient     *= attenuation;
    diffuse     *= attenuation;
    specular    *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
};