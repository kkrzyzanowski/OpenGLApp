#include "Sphere.h"



Sphere::Sphere() : Shape(Shapes::SPEHERE)
{
	const int sectors = 24;
	const int rings = 12;
	const int pointsCount = sectors * rings * (3 + 2);
	const int indexesValue = (rings) * (sectors - 1) * 6;
	GLfloat vertices[pointsCount * 2];
	//vertices.resize(pointsCount);
	// std::vector<GLfloat>::iterator i = vertices.begin();
	 unsigned int sphere_ix [indexesValue * 2];
	unsigned int sphere_vbo[4] = { -1, -1, -1, -1 };
	unsigned int sphere_vao[4] = { -1, -1, -1, -1 };
	
	float radius = 1.0f;
	float const S = 1. / (float)(sectors);
	float const R = 1. / (float)(rings-1);
	 int r, s;
	
	//normals.resize(rings * sectors * 3);
	//std::vector<GLfloat>::iterator n = normals.begin();
	float  y = 0.0f;
	float  x = 0.0f;
	float  z = 0.0f;
	int iy = 0;
	int index = 0;
	for(r=0;r<rings;r++) for (s = 0; s < sectors; s++, index+=5)
	{
		
		x = cos(2 * M_PI *s * S) * sin(M_PI * r * R);
		y = sin(-M_PI_2 + M_PI * r *R);
		z = sin(2 * M_PI * s * S) * sin(M_PI *r *R);
		
		vertices[index] = x * radius;
		vertices[index+1] = y;
		vertices[index+2] = z * radius;

		vertices[index+3] = s * S;
		vertices[index+4] = r*R;


	/*	*n++ = x;
		*n++ = y;
		*n++ = z;*/
	}
	//for (r = 0, index=pointsCount; r<rings; r++) for (s = 0; s < sectors; s++, index += 5)
	//{

	//	x = cos(2 * M_PI *s * S) * cos(M_PI * r * R);
	//	y = sin(-M_PI * r *R);
	//	z = sin(2 * M_PI * s * S) * cos(M_PI *r *R);

	//	vertices[index] = x * radius;
	//	vertices[index + 1] = y;
	//	vertices[index + 2] = z * radius;

	//	vertices[index + 3] = s * S;
	//	vertices[index + 4] = r * R;


	//}
	//

	for (index = 0, r = 0; r < rings; r++)
	{
		for (s = 0; s < sectors-1; s++)
		{
			/*sphere_ix[index] = iy; index++;
			sphere_ix[index] = iy + 1; index++;
			sphere_ix[index] = iy + sectors; index++;

			sphere_ix[index] = iy + sectors; index++;
			sphere_ix[index] = iy + 1; index++;
			sphere_ix[index] = iy + sectors + 1; index++;*/

			sphere_ix[index] = r * sectors + s; index++;
			sphere_ix[index] = (r + 1) * sectors + s; index++;
			sphere_ix[index] = (r+1) * sectors + s + 1; index++;

			sphere_ix[index] = (r + 1) * sectors + s + 1; index++;
			sphere_ix[index] = r  * sectors + s + 1; index++;
			sphere_ix[index] = r * sectors + s; index++;
			//*i++ = (r + 1) * sectors + s;
		}
	}
	//for (index = pointsCount, r = 0; r < rings - 1; r++)
	//{
	//	for (s = 0; s < sectors - 1; s++)
	//	{
	//		/*sphere_ix[index] = iy; index++;
	//		sphere_ix[index] = iy + 1; index++;
	//		sphere_ix[index] = iy + sectors; index++;

	//		sphere_ix[index] = iy + sectors; index++;
	//		sphere_ix[index] = iy + 1; index++;
	//		sphere_ix[index] = iy + sectors + 1; index++;*/

	//		sphere_ix[index] = r * sectors + s; index++;
	//		sphere_ix[index] = (r + 1) * sectors + s; index++;
	//		sphere_ix[index] = (r + 1) * sectors + s + 1; index++;

	//		sphere_ix[index] = (r + 1) * sectors + s + 1; index++;
	//		sphere_ix[index] = r * sectors + s + 1; index++;
	//		sphere_ix[index] = r * sectors + s; index++;
	//		//*i++ = (r + 1) * sectors + s;
	//	}
	//}
	CreateShape(vertices, sphere_ix);
}

void Sphere::CreateShape(const GLfloat * points, unsigned int * orderIndex)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	texture = new Texture("Images\\BrickMedievalBlocks0129_2_M.jpg");
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * 12 * 24 * 2* 3);

	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, 11 * 24 * 6 * 2); //indexes count
	GenerateShaders();
}

void Sphere::TurnOffShapeElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}

void Sphere::Update(glm::mat4 camView)
{
	sm.Bind();
	shaders[0]->SetUniformMat4f("u_camView", camView, sm.GetProgram());
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
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.6f, -0.8f, -.7f));
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.5f));
	proj = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
	mvp = proj * view * model;
}

void Sphere::GenerateShaders()
{
	shaders.push_back(new Shader("Shaders\\VertexShaderPlane.vert"));
	shaders.push_back(new Shader("Shaders\\FragmentShaderPlane.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	shaders[0]->SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
	texture->Bind();
	shaders[1]->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f, sm.GetProgram());
	shaders[1]->SetUniform1i("u_texture", 0, sm.GetProgram());
	shaders[1]->SetUniform3f("sunLight", 0.99f, 0.71f, 0.32f, sm.GetProgram());
	shaders[1]->SetUniform3f("skyLight", 0.51f, 0.80f, 0.92f, sm.GetProgram());
}
