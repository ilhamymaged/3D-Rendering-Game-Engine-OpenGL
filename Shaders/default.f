#version 460 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat4 view;
} fs_in;    

uniform sampler2D diffuseTexture;
uniform int materialType;
uniform vec3 color;

//Shadowing
uniform sampler2DArray shadowMap;
layout (std140) uniform LightSpaceMatrices
{
    mat4 lightSpaceMatrices[16];
};
uniform float cascadePlaneDistances[16];
uniform float farPlane;

uniform vec3 cameraPos;

struct DirectionalLight { vec3 direction; };
uniform DirectionalLight directionalLight;

uniform int cascadeCount;
float calcShadows(vec3 lightDir);

void main()
{
    vec3 baseColor;
    if(materialType == 0) baseColor = color;
    if(materialType == 1) baseColor = texture(diffuseTexture, fs_in.TexCoords).rgb;

    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(normalize(fs_in.Normal), lightDir), 0.0);
   
    float shadow = calcShadows(lightDir);
    vec3 lighting = baseColor * (diff * (1.0 - shadow) + 0.2);
    FragColor = vec4(lighting, 1.0);
}

float calcShadows(vec3 lightDir)
{
    vec4 fragPosViewSpace = fs_in.view * vec4(fs_in.FragPos, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    int layer = -1;
    for (int i = 0; i < cascadeCount; ++i)
    {
        if (depthValue < cascadePlaneDistances[i])
        {
            layer = i;
            break;
        }
    }

    if (layer == -1) layer = cascadeCount; // Use The Last One

    vec4 fragPosLightSpace = lightSpaceMatrices[layer] * vec4(fs_in.FragPos, 1.0);

    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    float currentDepth = projCoords.z;
    if (currentDepth  > 1.0) return 0.0f;
    vec3 normal = normalize(fs_in.Normal);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    if (layer == cascadeCount) bias *= 1 / (farPlane * 0.5f);
    else bias *= 1 / (cascadePlaneDistances[layer] * 0.5f);

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(
                        shadowMap,
                        vec3(projCoords.xy + vec2(x, y) * texelSize,
                        layer)
                        ).r; 
            shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0) shadow = 0.0;
    	
    return shadow;
}