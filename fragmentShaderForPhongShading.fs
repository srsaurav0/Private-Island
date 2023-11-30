#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};



struct PointLight {
    vec3 position;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct DirectionalLight {
    vec3 direction;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct SpotLight {
    vec3 position;
    vec3 direction;

    float cos_theta;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


#define NR_POINT_LIGHTS 9

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;

uniform DirectionalLight directionalLight;
uniform bool dirLightOn = true;
uniform bool dirAmbientLightOn = true;
uniform bool dirDiffuseLightOn = true;
uniform bool dirSpecularLightOn = true;

uniform SpotLight spotLight;
uniform bool spotLightOn = true;
uniform bool spotAmbientLightOn = true;
uniform bool spotDiffuseLightOn = true;
uniform bool spotSpecularLightOn = true;

// function prototypes
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V);

vec3 CalcDirectionalLight(Material material, DirectionalLight light, vec3 N, vec3 V);

vec3 CalcSpotLight(Material material, SpotLight light, vec3 N, vec3 fragPos, vec3 V);


void main()
{
    // properties
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    
    vec3 result;
    // point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(material, pointLights[i], N, FragPos, V);

    if(dirLightOn)
        result += CalcDirectionalLight(material, directionalLight, N, V);
    if(!dirAmbientLightOn)
        result += CalcDirectionalLight(material, directionalLight, N, V) - material.ambient;
    if(!dirDiffuseLightOn)
        result += CalcDirectionalLight(material, directionalLight, N, V) - material.diffuse;
    if(!dirSpecularLightOn)
        result += CalcDirectionalLight(material, directionalLight, N, V) - material.specular;

    if(spotLightOn)
        result += CalcSpotLight(material, spotLight, N, FragPos, V);
    if(!spotAmbientLightOn)
        result += CalcSpotLight(material, spotLight, N, FragPos, V) - material.ambient;
    if(!spotDiffuseLightOn)
        result += CalcSpotLight(material, spotLight, N, FragPos, V) - material.diffuse;
    if(!spotSpecularLightOn)
        result += CalcSpotLight(material, spotLight, N, FragPos, V) - material.specular;
      
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}


vec3 CalcDirectionalLight(Material material, DirectionalLight light, vec3 N, vec3 V)
{
    vec3 L = normalize(-light.direction);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(Material material, SpotLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;

    float cos_alpha = dot(L, normalize(-light.direction));
    float intensity;
    if(cos_alpha<light.cos_theta)
    {
        intensity = 0.0;
    }
    else
    {
        intensity = cos_alpha;
    }
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}