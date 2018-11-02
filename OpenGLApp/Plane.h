#include "Shape.h"
#include "ShapesBuilder.h"
class Plane: public Shape
{
public:
	Plane();
	Plane(const ShapesBuilder builder);
	void CreateShape(const GLfloat* points, unsigned int* orderIndex) override;
	void TurnOffShapeElements() override;
	void Update() override;
	void GenerateShaders() override;
	void GetSourceLight(glm::vec3 lightSource);
	~Plane();
private:
	void CreateMVPMatrix() override;
	glm::vec3 m_sourceLight;
	Texture* specularTexture;
};

