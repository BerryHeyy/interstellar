#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 vsNormal;
out vec3 vsPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vsNormal = mat3(model) * aNormal;
	vsPosition = vec4(model * vec4(aPos, 1.0)).xyz;

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
