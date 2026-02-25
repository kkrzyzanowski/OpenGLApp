#include "KernelSamplerGenerator.h"

std::vector<glm::vec3> KernelSamplerGenerator::GenerateKernelSamples()
{
	samples.clear();
	for (unsigned int i = 0; i < kernelSize; ++i)
	{
		glm::vec3 sample(randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator));
		sample = glm::normalize(sample);
		sample *= randomFloats(generator);
		float scale = float(i) / kernelSize;
		scale = 0.1f + 0.9f * scale * scale;
		sample *= scale;
		samples.push_back(sample);
	}
	return samples;
}

std::vector<glm::vec3> KernelSamplerGenerator::GenerateNoise()
{
	SSAOnoise.clear();
	for (unsigned int i = 0; i < noiseCount; i++)
	{
		glm::vec3 noise(randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator) * 2.0f - 1.0f, 0.0f);
		SSAOnoise.push_back(noise);
	}

	return SSAOnoise;
}

KernelSamplerGenerator::KernelSamplerGenerator() : randomFloats(0.0f, 1.0f), generator(std::random_device{}()), kernelSize(64), noiseCount(16)
{
}

KernelSamplerGenerator::KernelSamplerGenerator(unsigned int samples, unsigned int noiseCount) : randomFloats(0.0f, 1.0f), 
generator(std::random_device{}()), kernelSize(samples), noiseCount(noiseCount)
{
}
