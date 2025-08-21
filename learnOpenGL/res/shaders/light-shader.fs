#version 330 core

in vec4 vertexColor;
in vec4 vertexPosition;

out vec4 FragColor;

uniform vec4 lightColor;

void main()
{
   //FragColor = lightColor;
   //FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f) * vertexColor;
   FragColor = vec4(lightColor * vertexColor);
   //FragColor = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
}
