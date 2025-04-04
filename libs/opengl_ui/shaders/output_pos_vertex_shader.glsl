#version 460 core

layout (location = 0) in vec3 aPos;

out vec4 VertexPos;

void main()
{
    gl_Position = vec4(aPos.x - 0.25, aPos.y, aPos.z, 1.0);
    VertexPos = gl_Position;
}