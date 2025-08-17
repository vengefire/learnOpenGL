#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float offsetX;
out vec4 vertexColor;
out vec4 vertexPosition;

void main()
{
   gl_Position = vec4(aPos.x + offsetX, aPos.y, aPos.z, 1.0);
   vertexColor = vec4(aColor.xyz, 1.0f);
   vertexPosition = gl_Position;
}
