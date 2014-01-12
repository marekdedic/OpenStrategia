#version 400 core

in vec4 vColor;
in vec3 vPosition_w;
in vec3 vNormal_c;
in vec3 EyeDirection_c;
in vec3 LightDirection_c;

out vec4 fColor;

uniform vec3 LightPosition_w;

void main()
{
	vec3 LightColor = vec3(1, 1, 1);
	float LightPower = 50.0f;

	vec3 MaterialDiffuseColor = vPosition_w;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

	float distance = length(LightPosition_w - vPosition_w);

	// Normal of the computed fragment, in camera space
	vec3 fNormal_c = normalize(vNormal_c);
	// Direction of the light (from the fragment to the light)
	vec3 LightDirection_f = normalize(LightDirection_c);
	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(fNormal_c, l), 0, 1);
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_c);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l, fNormal_c);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(E, R), 0, 1);

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
}
