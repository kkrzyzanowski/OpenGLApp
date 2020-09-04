//#define GLM_ENABLE_EXPERIMENTAL
#include "Sphere.h"
#include "glm\gtx\rotate_vector.hpp"


Sphere::Sphere()
{
}

Sphere::Sphere(const ShapesBuilder builder) : Shape()
{
	sourceShapeType = builder.m_shapeType;
	camState = builder.m_view;
	light = builder.m_light;
	outsideLight = builder.m_pos;
	const int sectors = 24;
	const int rings = 12;
	const int pointsCount = sectors * rings * (3 + 2 + 3);
	const int indexesValue = (rings) * (sectors ) * 6;
	GLfloat vertices[pointsCount];

	 unsigned int sphere_ix [indexesValue];
	unsigned int sphere_vbo[4] = { -1, -1, -1, -1 };
	unsigned int sphere_vao[4] = { -1, -1, -1, -1 };
	
	radius = 1.0f;
	float const S = 1. / (float)(sectors);
	float const R = 1. / (float)(rings-1);
	 int r, s;
	

	float  y = 0.0f;
	float  x = 0.0f;
	float  z = 0.0f;
	int iy = 0;
	int index = 0;
	for(r=0;r<rings;r++) for (s = 0; s < sectors; s++, index+=8)
	{
		
		x = cos(2 * M_PI *s * S) * sin(-M_PI * r * R);
		y = sin(-M_PI_2 + M_PI * r *R);
		z = sin(2 * M_PI * s * S) * sin(-M_PI *r *R);
		
		vertices[index] = x * radius;
		vertices[index+1] = y;
		vertices[index+2] = z * radius;

		vertices[index+3] = s * S;
		vertices[index+4] = r*R;


		vertices[index+5] = x;
		vertices[index + 6] = y;
		vertices[index + 7] = z;
	}

	for (index = 0, r = 0; r < rings; r++)
	{
		for (s = 0; s < sectors; s++)
		{
			if (s + 1 < sectors)
			{
				sphere_ix[index] = r * sectors + s; index++;
				sphere_ix[index] = (r + 1) * sectors + s; index++;
				sphere_ix[index] = (r + 1) * sectors + s + 1; index++;

				sphere_ix[index] = (r + 1) * sectors + s + 1; index++;
				sphere_ix[index] = r * sectors + s + 1; index++;
				sphere_ix[index] = r * sectors + s; index++;
			}
			else

			{
				sphere_ix[index] = r * sectors + s; index++;
				sphere_ix[index] = (r + 1) * sectors + s; index++;
				sphere_ix[index] = (r + 1) * sectors + 0; index++;

				sphere_ix[index] = (r + 1) * sectors + 0; index++;
				sphere_ix[index] = r * sectors + 0; index++;
				sphere_ix[index] = r * sectors + s; index++;
			}
		}
	}

	physics = { 1.0f, glm::vec3(0.0f, -.01f, 0.0f),
		1.0f, 0.0f, true, glm::vec3(.0f, 10.0f, .0f) };
	CreateShape(vertices, sphere_ix, sectors*rings, indexesValue);
	CreateType();
	
}


void Sphere::Update()
{
	sm.Bind();
	for each(Texture* texture in textures)
		texture->Bind();
	mvp.model = glm::translate(mvp.model, physics.velocity);
	mvp.model = glm::rotate(mvp.model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mvpResult = mvp.proj * mvp.view * mvp.model;
	insideLightPos = glm::vec3(mvp.model[3][0], mvp.model[3][1], mvp.model[3][2]);
	shaders[0]->SetUniformMat4f("u_MVP", mvpResult, sm.GetProgram());
	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
}


Sphere::~Sphere()
{
}

void Sphere::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	insideLightPos = glm::vec3(0.0f, 1.8f, -10.7f);
	mvp.model = glm::translate(mvp.model, insideLightPos);
	mvp.model = glm::rotate(mvp.model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	normalLight = glm::vec3(0.0f, -1.0f, 0.0f);
	normalLight = glm::rotateZ(normalLight, glm::radians(30.0f));

	mvpResult = mvp.proj * mvp.view * mvp.model;
}

void Sphere::GenerateShaders()
{
	textures.push_back(new Texture("Images\\TexturesCom_Metal_RedHotSteel_1K_emissive.jpg", 0));
	shaders.push_back(new Shader("Shaders\\LightVertexShader.vert"));
	shaders.push_back(new Shader("Shaders\\LightFragmentShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	/*shaders[0]->SetUniformMat4f("model", model, sm.GetProgram());
	shaders[0]->SetUniformMat4f("view", view, sm.GetProgram());
	shaders[0]->SetUniformMat4f("projection", proj, sm.GetProgram());*/
	shaders[0]->SetUniformMat4f("u_MVP", mvpResult, sm.GetProgram());
	for each(Texture* texture in textures)
		texture->Bind();
	shaders[1]->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f, sm.GetProgram());
	shaders[1]->SetUniform1i("u_texture", 0, sm.GetProgram());
	shapeState = ShapeState::EXISTING;
}

glm::vec3 Sphere::GetNormal()
{
	return glm::vec3();
}

float Sphere::GetRadius()
{
	return radius;
}
