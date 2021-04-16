#include "../Shape.h"
#include "../ShapesBuilder.h"
class Plane: public Shape
{
public:
	Plane();
	Plane(const ShapesBuilder builder);
	void Update() override;
	void GenerateShaders() override;
	void GetSourceLight(glm::vec3 lightSource);
	void Translate(const glm::vec3& valueToMove);
	glm::vec3 GetNormal() override;
	~Plane();
private:
	void CreateMVPMatrix() override;
	glm::vec3 m_sourceLight;
	Texture* specularTexture;
};

