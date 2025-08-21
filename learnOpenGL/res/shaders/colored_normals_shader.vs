#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;

out vec4 vertexColor;
out vec3 vertexNormal;
out vec3 FragPosition;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    FragPosition = vec3(transform * vec4(aPos, 1.0));
	vertexNormal = mat3(transpose(inverse(transform))) * aNormal;
	vertexColor = aColor;

	gl_Position = projection * view * vec4(FragPosition, 1.0);
	// TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}