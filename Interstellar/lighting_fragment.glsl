#version 440 core

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 vsNormal;
in vec3 vsPosition;

out vec4 FragColor;

uniform Material material;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

void main()
{

	// Ambient light
	vec3 ambientLight = vec3(0.1, 0.1, 0.1);


	// Diffuse light
	vec3 posToLightDirVec = normalize(lightPos0 - vsPosition);
	vec3 diffuseColor = vec3(1.0f, 1.0f, 1.0f);
	float diffuse = clamp(dot(posToLightDirVec, vsNormal), 0, 1);
	vec3 diffuseFinal = diffuseColor * diffuse;

	// Specular light
	vec3 lightToPosDirVec = normalize(vsPosition - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vsNormal)));
	vec3 posToViewDirVec = normalize(cameraPos - vsPosition);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 100);
	vec3 specularFinal = vec3(1.0, 1.0, 1.0) * specularConstant;


	// Attenuation

	//Final light

	FragColor = vec4(1.0, 1.0, 1.0, 1.0) * (vec4(ambientLight, 1.0) + vec4(diffuseFinal, 1.0) + vec4(specularFinal, 1.0));
}