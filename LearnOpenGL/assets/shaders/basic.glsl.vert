#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	v_FragPos = vec3(u_Model * vec4(a_Position, 1.0f));

	gl_Position = u_Proj * u_View * u_Model * vec4(a_Position, 1.0f);
}