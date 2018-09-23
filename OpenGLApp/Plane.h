#include "Shape.h"
class Plane: public Shape
{
public:
	Plane();
	void CreateShape(const GLfloat* points, unsigned int* orderIndex) override;
	void TurnOffShapeElements() override;
	void Update(glm::mat4 camView) override;
	~Plane();
private:
	glm::mat4 mvp;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	void CreateMVPMatrix() override;
	void GenerateShaders() override;
};

