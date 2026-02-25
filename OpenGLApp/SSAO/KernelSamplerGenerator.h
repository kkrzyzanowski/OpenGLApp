#pragma once
#include <random>
#include <GLFW/glfw3.h>
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"

class KernelSamplerGenerator
{
public:
	KernelSamplerGenerator();
	KernelSamplerGenerator(unsigned int samples, unsigned int noiseCount);
	std::vector<glm::vec3> GenerateKernelSamples();
	std::vector<glm::vec3> GenerateNoise();
private:
	std::uniform_real_distribution<GLfloat> randomFloats;
	std::default_random_engine generator;
	std::vector<glm::vec3> samples;
	std::vector<glm::vec3> SSAOnoise;
	unsigned int kernelSize;
	unsigned int noiseCount;
};