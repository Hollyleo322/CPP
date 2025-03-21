#version 330 core
in vec4 position;
in vec4 inColor;

flat out vec3 vertPos;
out vec4 vertexColor; 

void main()
{
    gl_Position = position;
    vertexColor = inColor;
    vertPos     = position.xyz / position.w;
}
