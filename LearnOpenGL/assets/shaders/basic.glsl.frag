#version 330 core

out vec4 o_Color;

in vec3 v_Normal;
in vec3 v_FragPos;
in vec2 v_TexCoord;

struct Material 
{
	sampler2D Texture;
	sampler2D Specular;
	float Shininess;
};

struct Light
{
	vec3 Position;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform Light u_Light;

void main()
{	

	vec3 normal = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.Position - v_FragPos);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
	
	vec3 ambient =  u_Light.Ambient * vec3(texture(u_Material.Texture, v_TexCoord));
	vec3 diffuse = u_Light.Diffuse * diff * vec3(texture(u_Material.Texture, v_TexCoord)); 
	vec3 specular = u_Light.Specular * spec * vec3(texture(u_Material.Specular, v_TexCoord));

	o_Color = vec4((ambient + diffuse + specular), 1.0);
}