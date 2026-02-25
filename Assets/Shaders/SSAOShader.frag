#version 330 core

out float FragColor;

in vec2 TexCoords;

uniform sampler2D pos;
uniform sampler2D normal;
uniform sampler2D noise;

uniform vec3 samples[64];

int kernelSize = 64;
float radius = 0.64;
float bias = 0.025;


vec2 noiseScale = vec2(1920.0/4.0, 1080/4.0);
uniform mat4 projection;

void main()
{
    vec3 FragPos = texture(pos, TexCoords).rgb;
    vec3 Normal = normalize(texture(normal, TexCoords).rgb);
    vec3 RandomVec = normalize(texture(noise, TexCoords * noiseScale).rgb);

    vec3 tangent = normalize(RandomVec - Normal * dot(RandomVec, Normal));
    vec3 bitangent = cross(Normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, Normal);

    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; ++i)
    {
        vec3 samplePos = TBN * samples[i];
        samplePos = FragPos + samplePos * radius;

        vec4 offset = projection * vec4(samplePos, 1.0);
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;

        float sampleDepth = texture(pos, offset.xy).z;

        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(FragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;
    }

    occlusion = 1.0 - (occlusion / kernelSize);
    FragColor = occlusion;
}