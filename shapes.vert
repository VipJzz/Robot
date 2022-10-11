#version 330 core
layout(location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;



out vec3 Normal;
out vec3 FragPos;
uniform mat4 RotMatrix ;

//3D
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{


    Normal=aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view *vec4(FragPos, 1.0f);
    // gl_Position = projection * view * model *vec4(aPos.x,aPos.y,aPos.z, 1.0f);
   // TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);//y反转

}
