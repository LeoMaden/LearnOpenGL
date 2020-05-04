#version 330 core

out vec4 o_Color;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

void main()
{
	float ambientStrength = 0.1;
	float specularStrength = 0.5;
	vec3 objColor = vec3(0.8, 0.2, 0.3);

	vec3 normal = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_FragPos);

	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

	vec3 ambient = ambientStrength * u_LightColor;
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * u_LightColor;
	vec3 specular = specularStrength * spec * u_LightColor;

	o_Color = vec4((ambient + diffuse + specular) * objColor, 1.0);
}