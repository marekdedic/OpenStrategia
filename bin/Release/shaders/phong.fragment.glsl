#version 400 core

in vec4 vNormal_w;
in vec4 toCamera;
in vec4 toLight;

out vec4 fColor;

uniform float lFalloffMin;
uniform float lFalloffMax;

void main()
{
    float phongExp = 5;
    vec4 lDiffuseColor = vec4(0.6, 0.6, 0.6, 1);
    vec4 lSpecularColor = lDiffuseColor;
    vec4 mDiffuseColor = vec4(0.3, 0.5, 0.5, 1);
    vec4 mSpecularColor = mDiffuseColor;
    vec4 mAmbientColor = mDiffuseColor;
    vec4 gAmbientColor = vec4 (0.2, 0.2, 0.2, 1);

    // Diffuse component
    float cosDiff = clamp(dot(vNormal_w, toLight), 0, 1);
    vec4 fDiffuseColor = cosDiff * mDiffuseColor * lDiffuseColor;

    // Specular component
    vec4 reflection = 2 * dot(vNormal_w, toLight) * vNormal_w - toLight;
    float cosSpec = clamp(dot(reflection, toCamera), 0, 1);
    vec4 fSpecularColor = pow(cosSpec, phongExp) * mSpecularColor * lSpecularColor;

    // Ambient component
    vec4 fAmbientColor = mAmbientColor * gAmbientColor;

    // Light Attenuation
    float lDistance = length(toLight);
    float lFalloffMultiplier;
    if(lDistance <= lFalloffMin)
    {
        lFalloffMultiplier = 1;
    }
    else if(lDistance >= lFalloffMax)
    {
        lFalloffMultiplier = 0;
    }
    else
    {
        lFalloffMultiplier = (lFalloffMax - lDistance) / (lFalloffMax - lFalloffMin);
    }

	fColor = lFalloffMultiplier * (fDiffuseColor + fSpecularColor) + fAmbientColor;
}
