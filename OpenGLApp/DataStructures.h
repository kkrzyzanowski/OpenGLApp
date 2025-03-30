#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

typedef std::vector<glm::vec3> Vertices;
typedef std::vector<std::array<glm::vec3, 2>> Edges;
typedef std::vector<std::array<glm::vec3, 3>> Triangles;
typedef std::vector<std::vector<std::array<glm::vec3, 3>>> Faces;
typedef std::array<glm::vec3, 3> Triangle;
 struct MVP
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};
 struct RGB
 {
	 uint8_t r;
	 uint8_t g;
	 uint8_t b;
 };

 struct ShapeParameters
 {
	 std::vector<glm::vec2> textCoords;
	 std::vector<glm::vec3> normals;
 };

 struct ShapeElements
 {
	 Vertices vertices;
	 Edges edges;
	 Triangles triangles;
	 Faces faces;
 };

 struct SimpleLight
 {
	 glm::vec3 position;
	 glm::vec3 color;
	 unsigned short slot;
	 unsigned short lightNumber;
 };

 template<typename T, size_t SIZE>
 size_t getSize(T(&)[SIZE]) 
 {
	 return SIZE;
 };