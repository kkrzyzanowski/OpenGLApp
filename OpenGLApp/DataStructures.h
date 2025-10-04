#pragma once
#include <vector>
#include <variant>
#include <functional>
#include <array>
#include "Enums.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

struct MVP;
struct SimpleLight;
class Shader;
using ShaderParams = std::variant<glm::mat4, glm::vec3, glm::vec4, MVP, bool, float, unsigned int, unsigned short, std::vector<SimpleLight>>;
using ShaderFunction = std::function<void(std::vector<Shader*>&, unsigned int, std::vector<ShaderParams>&)>;

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

 struct ShaderProperties
 {
	 ShaderFunctionType type;
	 std::vector<ShaderParams> params;
 };

 struct Paths
 {
	 std::vector<const char*> shadersPaths;
	 std::vector<const char*> texturesPaths;
 };
