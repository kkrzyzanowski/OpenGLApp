#include <algorithm>
#include <time.h>
#include <string>
#include "Shape.h"
#include "Renderer.h"
#include "glm/gtx/rotate_vector.hpp"

static bool RandomInitializer = false;
Shape::Shape()
{
	
	shapeState = ShapeState::CREATING;
	sourceShapeType = SourceShapeType::NO_TYPE;
	do
	{
		this->Id = GenerateId(this->rgbCheck);
	} while (std::find(shape_ids.begin(), shape_ids.end(), this->Id) != shape_ids.end());
	sm.ActivateProgram("ShapeShader");
	Selected = false;
	
}

Shape::Shape(ShapeType t):Shape()
{
	shapeType = t;
}

Shape::Shape(SourceShapeType sourceType)
{
	shapeState = ShapeState::CREATING;
	sourceShapeType = sourceType;
}

void Shape::CreateShape(const GLfloat* points, unsigned int * orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3 + 2 + 3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes); //indexes count
}

void Shape::CreateShapev2(const GLfloat*& points, unsigned int*& orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3 + 2 + 3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes); //indexes count
}

VertexArray* Shape::GetVertexArray()
{
	return va;
}

VertexBuffer* Shape::GetVertexBuffer()
{
	return vb;
}

IndexBuffer* Shape::GetIndexBuffer()
{
	return ib;
}
ShaderManager Shape::GetShaderManager()
{
	return sm;
}
Texture * Shape::GetTexture(std::string name)
{
	auto it = std::find_if(textures.begin(), textures.end(), [&name](Texture* tex) {return tex->GetTextureName() == name; });
	return *it;
}

void Shape::TurnOffShapeElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}
void Shape::InitializeShapeView(glm::mat4& view)
{
	this->mvp.view = view;
}
glm::vec3 Shape::GetShapeCenterPoint()
{
	return shapeCoords;
}
void Shape::ApplyProjectionMatrix(glm::mat4 proj)
{
	this->mvp.proj = proj;
}
void Shape::SetOutsideLight(glm::vec3& light)
{
	if(sourceShapeType == SourceShapeType::DIFFUSE)
		outsideLight = light;
}
void Shape::SetEyeCamPos(glm::vec3 & pos)
{
	camEyePos = pos;
}
SourceShapeType Shape::GetSourceShapeType()
{
	return sourceShapeType;
}

void Shape::RotateNormals(float rotation, glm::vec3 rotationAxis)
{
	for(glm::vec3& normal : normals)
	{
		normal = glm::rotate(normal, glm::radians(rotation), rotationAxis);
		std::cout << "Normal x: " << normal.x << " Normal y: " << normal.y << " Normal z: "
			<< normal.z << std::endl;
	}
}
void Shape::Translate(Direction dir, float value)
{
	switch (dir)
	{
	case UP:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, value, 0.0f));
		break;
	case DOWN:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, -value, 0.0f));
		break;
	case LEFT:
		mvp.model = glm::translate(mvp.model, glm::vec3(-value , 0.0f, 0.0f));
		break;
	case RIGHT:
		mvp.model = glm::translate(mvp.model, glm::vec3(value, 0.0f, 0.0f));
		break;
	case FORWARD:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, 0.0f, value));
		break;
	case BACKWARD:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, 0.0f, -value));
		break;
	default:
		break;
	}
}
void Shape::Scale(float value)
{
}
void Shape::Rotate(float value)
{
}
glm::vec3 Shape::GetInsideLight()
{
	return insideLightPos;
}
ShapeState Shape::GetCreationState()
{
	return shapeState;
}
std::array<float, 3> Shape::GetPosition()
{
	return std::array<float, 3>({mvpResult[3][0], mvpResult[3][1], mvpResult[3][2]});
}

ShapeType Shape::GetType()
{
	return ShapeType();
}



void Shape::InitializePickedShape()
{
	if (stencilOutline != nullptr)
	{
		stencilOutline = new StencilOutline();
	}

	stencilOutline->InitializePerspective(this->mvp.proj);
	stencilOutline->InitializeView(this->mvp.view);
	stencilOutline->InitializeModel(this->mvp.model);
	stencilOutline->CalculateMvpResult();
	stencilOutline->UseShader();
}
void Shape::UpdatePickedShape()
{
	stencilOutline->InitializeView(mvp.view);
	stencilOutline->Update();
	ib->Bind();
	va->Bind();
	
}
//Shape::~Shape()
//{
//	GLCall(glDisableVertexAttribArray(0));
//}

void Shape::CreateType()
{
	switch (sourceShapeType)
	{
	case SourceShapeType::DIFFUSE:
	{
		type = new DiffuseShape();
		break;
	}
	case SourceShapeType::LIGHT:
	{
		type = new LightShape();
		break;
	}
	case SourceShapeType::PARTICLE:
	{
		type = new ParticleShape();
		break;
	}
	default:
		break;
	}
}
void Shape::GeneratePickedShaders()
{
	pickedShaders.push_back(new Shader("Shaders\\PickingVertexShader.vert"));
	pickedShaders.push_back(new Shader("Shaders\\PickingFragmentShader.frag"));
	sm.CreateProgram("picked");
	sm.ActivateProgram("picked");
	sm.AddShadersToProgram(pickedShaders);
	sm.Bind();
	ShaderTypeGenerator::PickedShaderGenerator(pickedShaders, glm::vec3(rgbCheck.r/255.0f, rgbCheck.g/255.0f, rgbCheck.b/255.0f), mvpResult, sm.GetProgram("picked"));
	sm.UnBind();
	sm.ActivateProgram("ShapeShader");
}
unsigned long GenerateId(RGB &rgb)
{
	const int size = 8;
	const int idSize = 24;

if(!RandomInitializer)
{ 
	srand(time(NULL));
	RandomInitializer = true;
}

	rgb.r = rand() % 255;
	rgb.g = rand() % 255;
	rgb.b = rand() % 255;

	std::string id = std::to_string(rgb.r) + std::to_string(rgb.g) + std::to_string(rgb.b);

	return std::stol(id);
	
}


std::vector<std::vector<std::array<glm::vec3, 3>>> Shape::GetFaces(std::vector<std::array<glm::vec3, 3>>& triangles)
{
	std::vector<std::vector<std::array<glm::vec3, 3>>> faces;
	std::vector<std::array<glm::vec3, 3>> triangleUnused;
	for each (std::array<glm::vec3, 3> triangle in triangles)
	{
		bool match = false;
		size_t matchedIndex = 0;
		for each (std::array<glm::vec3, 3> ut in triangleUnused)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0, vertexMatch = 0; k < 3; k++)
					{
						if (triangle[i][k] == ut[j][k])
						{
							vertexMatch++;
							if (vertexMatch > 1 && triangle[i] != ut[j])
							{
								match = true;
								std::vector <std::array<glm::vec3, 3>> face = { triangle, ut };
								faces.push_back(face);
								std::vector<std::array<glm::vec3, 3>>::iterator itr = std::find(triangleUnused.begin(), triangleUnused.end(), ut);
								matchedIndex = std::distance(triangleUnused.begin(), itr);
								break;
							}

						}
					}
					if (match)
						break;
				}
				if (match)
					break;
			}
			if (match)
			{
				triangleUnused.erase(triangleUnused.begin() + matchedIndex);
				matchedIndex = 0;
				break;
			}
		}
		if (!match)
			triangleUnused.push_back(triangle);
		else
			match = false;
	}
	return faces;
}

std::vector<std::array<glm::vec3, 3>> Shape::GetTriangles(std::vector<glm::vec3>& vertices, size_t* indices, int indices_count)
{
	std::vector<std::array<glm::vec3, 3>> triangles;
	std::array<glm::vec3, 3> vertex;
	for (int i = 0; i < indices_count; i++)
	{
		vertex[i%3] = vertices[indices[i]];
		if (i % 3 == 2)
		{
			triangles.push_back(vertex);
			vertex.fill(glm::vec3());
		}
	}
	return triangles;
}

std::vector<glm::vec3> Shape::GetVertices(GLfloat* objectData, size_t elements)
{
	std::vector<glm::vec3> vertices;
	for (int i = 0; i < elements; i += 8)
	{
		vertices.push_back(glm::vec3(objectData[i], objectData[i + 1], objectData[i + 2]));
	}
	return vertices;
}


std::vector<std::array<glm::vec3, 2>> Shape::GetEdges(GLfloat* objectData)
{
	std::vector<std::array<glm::vec3, 2>> edges;
	int elements = *(&objectData + 1) - objectData; // getting size of array
	std::vector<glm::vec3> vertices;
	for (int i = 0, steps = 0; i < elements; i + 8, steps++)
	{
		glm::vec3 vertex = { objectData[i], objectData[i + 1], objectData[i + 2] };
		vertices.push_back(vertex);
		if (steps == 2)
		{
			glm::vec3 previousVertex;
			bool axisRepeat[3] = { true, true, true };
			for (int j = 0; j < vertices.size(); j++)
			{
				if (j == 0)
				{
					previousVertex = vertices[j];
					continue;
				}
				if (vertices[j].x != previousVertex.x)
				{
					axisRepeat[0] = false;
				}
				if (vertices[j].y != previousVertex.y)
				{
					axisRepeat[1] = false;
				}
				if (vertices[j].z != previousVertex.z)
				{
					axisRepeat[2] = false;
				}
			}
			for (int j = 0; j < 3; j++)
			{
				if (!axisRepeat[j])
				{
					if (vertices[j][j] == vertices[j + 1][j])
					{
						edges.push_back(std::array<glm::vec3, 2>({ vertices[j], vertices[j + 1] }));
						break;
					}
					else
					{
						edges.push_back(std::array<glm::vec3, 2>({ vertices[j], vertices[j + 2] }));
						break;
					}
				}
			}
			steps = 0;
		}
	}
	return edges;
}

void Shape::TranslatePoints(glm::mat4& mvp, Vertices& verts)
{
	for (auto iterator = verts.begin(); iterator != verts.end(); iterator++)
	{
		glm::vec4 point4f = glm::vec4(iterator->x, iterator->y, iterator->z, 1.0f);
		point4f = mvp * point4f;
		iterator->x = point4f.x;
		iterator->y = point4f.y;
		iterator->z = point4f.z;

	}
}

Triangles Shape::GetTriangles()
{
	return shapeElements.triangles;
}
