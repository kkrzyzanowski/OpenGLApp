#pragma once
#include "..\Shapes\Shape.h"
#include "..\Primitive.h"

class Line :
	public Shape, public Primitive
{
public:
	Line(ShapesBuilder& builder);
	Line(ShapesBuilder&& builder);
	void Create(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int dataSize);
	glm::vec3 GetNormal()  override;
	void Update() override;
	void Translate(const glm::vec3& valueToMove) override;
	void SetPoints(std::vector<glm::vec3> points) override;
	~Line();

	std::vector<glm::vec3> points;
protected:
	void CreateMVPMatrix() override;
private:
	std::vector<Shader*> shaders;
	ShaderCompiler sm;
};

