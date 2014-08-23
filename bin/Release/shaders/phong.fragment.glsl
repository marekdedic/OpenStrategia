#version 400 core

in vec4 vNormal_w;
in vec4 vToCamera_w;
in vec4 vToLight_w;
in vec2 fUV;

uniform float lFalloffMin;
uniform float lFalloffMax;
uniform sampler2D oSampler;

void main()
{
    float phongExp = 1;
    vec4 lDiffuseColor = vec4(0.3, 0.3, 0.3, 1);
    vec4 lSpecularColor = lDiffuseColor;
    vec4 mDiffuseColor = texture(oSampler, fUV);
    vec4 mSpecularColor = mDiffuseColor;
    vec4 mAmbientColor = mDiffuseColor;
    vec4 gAmbientColor = vec4 (0.2, 0.2, 0.2, 1);

    // Diffuse component
    float cosDiff = clamp(dot(vNormal_w, -vToLight_w), 0, 1);
    vec4 fDiffuseColor = cosDiff * mDiffuseColor * lDiffuseColor;

    // Specular component
    vec4 vReflection_w = reflect(-vToLight_w, vNormal_w);
    float cosSpec = clamp(dot(vReflection_w, vToCamera_w), 0, 1);
    vec4 fSpecularColor = pow(cosSpec, phongExp) * mSpecularColor * lSpecularColor;

    // Ambient component
    vec4 fAmbientColor = mAmbientColor * gAmbientColor;

    // Light Attenuation
    float lDistance = length(vToLight_w);
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

	gl_FragColor = lFalloffMultiplier * (fDiffuseColor + fSpecularColor) + fAmbientColor;
	//gl_FragColor = mDiffuseColor;
}
