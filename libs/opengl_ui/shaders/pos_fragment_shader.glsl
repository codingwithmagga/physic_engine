#version 460 core

out vec4 FragColor;
in vec4 VertexPos;

void main()
{
    FragColor = VertexPos;
}