#version 400 core

in vec4 vNormal_w;
in vec4 toCamera;
in vec4 toLight;

out vec4 fColor;

void main()
{
    float phongExp = 5;
    vec4 lDiffuseColor = vec4(0.6, 0.6, 0.6, 1);
    vec4 lSpecularColor = lDiffuseColor;
    vec4 mDiffuseColor = vec4(0.3, 0.5, 0.5, 1);
    vec4 mSpecularColor = mDiffuseColor;
    vec4 mAmbientColor = mDiffuseColor;
    vec4 gAmbientColor = vec4 (0.3, 0.3, 0.3, 1);

    // Diffuse component
    float cosDiff = clamp(dot(vNormal_w, toLight), 0, 1);
    vec4 fDiffuseColor = cosDiff * mDiffuseColor * lDiffuseColor;

    // Specular component
    vec4 reflection = 2 * dot(vNormal_w, toLight) * vNormal_w - toLight;
    float cosSpec = clamp(dot(reflection, toCamera), 0, 1);
    vec4 fSpecularColor = pow(cosSpec, phongExp) * mSpecularColor * lSpecularColor;

    // Ambient component
    vec4 fAmbientColor = mAmbientColor * gAmbientColor;

	fColor = fDiffuseColor + fSpecularColor + fAmbientColor;
}
