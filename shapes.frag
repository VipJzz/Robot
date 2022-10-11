#version 330 core
out vec4 FragColor;
//材质属性
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
//光源属性
struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D textureWall;
uniform mat4 RotMatrix ;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
    // 环境光
    vec3 ambient = light.ambient * material.ambient;//light可以控制环境光

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDirdot = normalize(lightPos - FragPos);//点光源
    vec3 lightDirpara = normalize(-light.direction);//平行光
    float diff = max(dot(norm, lightDirdot), 0.0);
    vec3 diffuse = light.diffuse  * (diff * material.diffuse);

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDirpara, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    //


    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
   // FragColor = vec4(lightColor * objectColor, 1.0);
}
