#pragma once
#include "Shape.h"
#include "Primitive.h"

class Line :
	public Shape, public Primitive
{
public:
	Line();
	void CreateShape(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes = 0) override;
	glm::vec3 GetNormal()  override;
	void GenerateShaders() override;
	void Update() override;
	void Translate(glm::vec3 valueToMove) override;
	void SetPoints(std::vector<glm::vec3> points) override;
	~Line();

	std::vector<glm::vec3> points;
protected:
	void CreateMVPMatrix() override;
private:
	std::vector<Shader*> shaders;
	ShaderManager sm;
};

