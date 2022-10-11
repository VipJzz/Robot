#version 330 core
out vec4 FragColor;

uniform int axisIndex;

void main()
{
    if(axisIndex == 1)
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else if(axisIndex == 2)
    {
        FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else if(axisIndex == 3)
    {
        FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
}
