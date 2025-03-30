#include "VerticesCreator.h"
#include <cmath>
#include <vector>
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"

VerticesShape* CreateSphere(int rings, int sectors, unsigned short bufferSize, float radius)
{
	{
		unsigned int pointsCount = sectors * rings * (bufferSize);
		unsigned int indexesValue = (rings - 1) * (sectors) * 6;
		float* vertices = new float[pointsCount];
		size_t* sphere_ix = new size_t[indexesValue];

		float const S = 1.0f / (float)(sectors);
		float const R = 1.0f / (float)(rings - 1);
		int r, s;


		float  y = 0.0f;
		float  x = 0.0f;
		float  z = 0.0f;
		int iy = 0;
		int index = 0;
		unsigned int usedBufferSize = 0;
		for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++, index += bufferSize)
		{

			x = cos(2 * M_PI * s * S) * sin(-M_PI * r * R);
			y = sin(-M_PI_2 + M_PI * r * R);
			z = sin(2 * M_PI * s * S) * sin(-M_PI * r * R);

			vertices[index] = x * radius;
			vertices[index + 1] = y;
			vertices[index + 2] = z * radius;
			usedBufferSize += 3;
			if (usedBufferSize < bufferSize)
			{
				vertices[index + 3] = s * S;
				vertices[index + 4] = r * R;
				usedBufferSize += 2;
			}
			if (usedBufferSize < bufferSize)
			{
				vertices[index + 5] = x;
				vertices[index + 6] = y;
				vertices[index + 7] = z;
			}
			usedBufferSize = 0;
		}

		for (index = 0, r = 0; r < rings - 1; r++)
		{
			for (s = 0; s < sectors; s++)
			{
				if (s + 1 < sectors)
				{
					// Normal case
					sphere_ix[index] = r * sectors + s; index++;
					sphere_ix[index] = (r + 1) * sectors + s; index++;
					sphere_ix[index] = (r + 1) * sectors + s + 1; index++;

					sphere_ix[index] = (r + 1) * sectors + s + 1; index++;
					sphere_ix[index] = r * sectors + s + 1; index++;
					sphere_ix[index] = r * sectors + s; index++;
				}
				else
				{
					// Special case for closing the ring
					sphere_ix[index] = r * sectors + s; index++;
					sphere_ix[index] = (r + 1) * sectors + s; index++;
					sphere_ix[index] = (r + 1) * sectors + 0; index++;

					sphere_ix[index] = (r + 1) * sectors + 0; index++;
					sphere_ix[index] = r * sectors + 0; index++;
					sphere_ix[index] = r * sectors + s; index++;
				}
			}
		}
		VerticesShape* sphere = new VerticesShape
		{
			pointsCount/bufferSize,
			indexesValue,
			vertices,
			sphere_ix
		};
		return sphere;
	}
}

VerticesShape* CreateCube(float size, unsigned int bufferSize)
{
	float halfSize = size * 0.5f;
	float* bufferData = new float[]{
		// front
		-halfSize, -halfSize, halfSize, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//0
		halfSize, -halfSize, halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//3
		halfSize, halfSize, halfSize, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//2

		halfSize, halfSize, halfSize, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//10
		-halfSize, halfSize, halfSize, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f / sqrt(3.0f),//9
		-halfSize, -halfSize, halfSize, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f / sqrt(3.0f),//8

		// left
		-halfSize, -halfSize, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,// 4
		-halfSize, -halfSize, halfSize, 1.0f, 0.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,//16
		-halfSize,  halfSize, halfSize, 1.0f, 1.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,//1

		-halfSize, halfSize, halfSize, 1.0f, 1.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,//17
		-halfSize, halfSize, 0.0f, 0.0f, 1.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,// 12
		-halfSize, -halfSize, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,// 5

		//top
		-halfSize, halfSize, halfSize, 0.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, // 6
		halfSize, halfSize,  halfSize, 1.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,// 7
		halfSize, halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,//11

		halfSize, halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,// 13
		-halfSize, halfSize, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,// 14
		-halfSize, halfSize, halfSize, 0.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,//15

		//right
		halfSize, halfSize, halfSize, 1.0f, 1.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,//18
		halfSize, -halfSize, halfSize, 0.0f, 1.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,//19
		halfSize, -halfSize, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,// 20

		halfSize, -halfSize, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,// 21
		halfSize, halfSize, 0.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,// 22
		halfSize, halfSize, halfSize, 1.0f, 1.0f, 1.0f / sqrt(3.0f), -0.0f, 0.0f,// 23

		//back
		halfSize, halfSize, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 6
		halfSize, -halfSize, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 7
		-halfSize, -halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//11

		-halfSize, -halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 13
		-halfSize, halfSize, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 14
		halfSize, halfSize, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//15


		//bottom
		halfSize, -halfSize, halfSize, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),//18
		-halfSize, -halfSize, halfSize, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),//19
		-halfSize, -halfSize, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),// 20

		-halfSize, -halfSize, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),// 21
		halfSize, -halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),// 22
		halfSize, -halfSize, halfSize, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f)// 23
	};

	unsigned int* indexes = new unsigned int[]
	{
		0, 1, 2,
		3, 4, 5, // front
		6, 7, 8,
		9, 10, 11, // left
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35,
	}; // bottom
	VerticesShape* cube = new VerticesShape
	{
		36,
		36,
		bufferData,
		indexes
	};
	return cube;
}

VerticesShape* CreatePlane(float size)
{
	std::vector<glm::vec3> positions = { glm::vec3(-.5f, 0.0f, -.5f),
									glm::vec3(.5f, 0.0f, -.5f),
									glm::vec3(-.5f, 0.0f, .5f),
									glm::vec3(.5f, 0.0f, .5f)
	};
	std::vector<glm::vec2> texCoords = { glm::vec2(0.0f, 0.0f),
									glm::vec2(1.0f, 0.0f),
									glm::vec2(0.0f, 1.0f),
									glm::vec2(1.0f, 1.0f)
	};
	std::vector<glm::vec3> normals = { glm::vec3(0.0f, 1.0f, 0.0f),
										glm::vec3(0.0f, 1.0f, 0.0f),
										glm::vec3(0.0f, 1.0f, 0.0f),
										glm::vec3(0.0f, 1.0f, 0.0f) };
	
	glm::vec3 edge1 = positions[0] - positions[1];
	glm::vec3 edge2 = positions[2] - positions[1];
	glm::vec2 deltaUV1 = texCoords[0] - texCoords[1];
	glm::vec2 deltaUV2 = texCoords[2] - texCoords[1];

	float f1 = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 bitangent1 = {
	f1 * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
	f1 * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
	f1 * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z),
	};
	glm::vec3 tangent1 = {
		f1 * (-deltaUV2.y * edge1.x + deltaUV1.x * edge2.x),
		f1 * (-deltaUV2.y * edge1.y + deltaUV1.x * edge2.y),
		f1 * (-deltaUV2.y * edge1.z + deltaUV1.x * edge2.z),
	};

	glm::vec3 edge3 = positions[2] - positions[1];
	glm::vec3 edge4 = positions[3] - positions[1];
	glm::vec2 deltaUV3 = texCoords[2] - texCoords[1];
	glm::vec2 deltaUV4 = texCoords[3] - texCoords[1];


	float f2 = 1.0f / (deltaUV3.x * deltaUV4.y - deltaUV4.x * deltaUV3.y);

	glm::vec3 bitangent2 = {
		f2 * (deltaUV4.y * edge3.x - deltaUV3.y * edge4.x),
		f2 * (deltaUV4.y * edge3.y - deltaUV3.y * edge4.y),
		f2 * (deltaUV4.y * edge3.z - deltaUV3.y * edge4.z),
	};
	glm::vec3 tangent2 = {
		f2 * (-deltaUV4.y * edge3.x + deltaUV3.x * edge4.x),
		f2 * (-deltaUV4.y * edge3.y + deltaUV3.x * edge4.y),
		f2 * (-deltaUV4.y * edge3.z + deltaUV3.x * edge4.z),
	};
	float* bufferData = new float[] {
		positions[0].x, positions[0].y, positions[0].z, texCoords[0].x, texCoords[0].y, normals[0].x, normals[0].y, normals[0].z, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,//0
		positions[1].x, positions[1].y, positions[1].z, texCoords[1].x, texCoords[1].y, normals[1].x, normals[1].y, normals[1].z, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z, //1
		positions[2].x, positions[2].y, positions[2].z, texCoords[2].x, texCoords[2].y, normals[2].x, normals[2].y, normals[2].z, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,//2

		positions[1].x, positions[1].y, positions[1].z, texCoords[1].x, texCoords[1].y, normals[1].x, normals[1].y, normals[1].z, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,//0
		positions[3].x, positions[3].y, positions[3].z, texCoords[3].x, texCoords[3].y, normals[3].x, normals[3].y, normals[3].z, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z, //1
		positions[2].x, positions[2].y, positions[2].z, texCoords[2].x, texCoords[2].y, normals[2].x, normals[2].y, normals[2].z, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,//3
	};

	unsigned int* indexes = new unsigned int[]
	{
		0, 1, 2,
		4, 5, 3
	};

	VerticesShape* plane = new VerticesShape
	{
		6,
		6,
		bufferData,
		indexes
	};
	return plane;
}
