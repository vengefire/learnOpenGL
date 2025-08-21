#version 330 core

in vec4 vertexColor;
in vec4 vertexPosition;

out vec4 FragColor;

void main()
{
   FragColor = vertexColor;
   //FragColor = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
}
