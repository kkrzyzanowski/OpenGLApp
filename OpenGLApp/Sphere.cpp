#include "Sphere.h"



Sphere::Sphere() : Shape()
{
	const int sectors = 24;
	const int rings = 12;
	const int pointsCount = sectors * rings * (3 + 2 + 3);
	const int indexesValue = (rings) * (sectors ) * 6;
	GLfloat vertices[pointsCount];

	 unsigned int sphere_ix [indexesValue];
	unsigned int sphere_vbo[4] = { -1, -1, -1, -1 };
	unsigned int sphere_vao[4] = { -1, -1, -1, -1 };
	
	float radius = 1.0f;
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
	state = CamView::STATIC;
	CreateShape(vertices, sphere_ix);
	
}

void Sphere::CreateShape(const GLfloat * points, unsigned int * orderIndex)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	texture = new Texture("Images\\TexturesCom_Metal_RedHotSteel_1K_emissive.jpg");
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * 12 * 24 * (2+ 3+ 3));

	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, 12 * 24 * 6); //indexes count
}

void Sphere::TurnOffShapeElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}

void Sphere::Update()
{
	sm.Bind();
	texture->Bind();
	mvp = proj * view * model;
	shaders[0]->SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
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
	insideLightPos = glm::vec3(0.6f, 1.8f, -.7f);
	model = glm::translate(model, insideLightPos);
	//view = glm::rotate(view, glm::radians(45.0f), glm::vec3(.4f, 0.0f, 1.0f));
	proj = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
	mvp = proj * view * model;
}

void Sphere::GenerateShaders()
{
	shaders.push_back(new Shader("Shaders\\LightVertexShader.vert"));
	shaders.push_back(new Shader("Shaders\\LightFragmentShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	/*shaders[0]->SetUniformMat4f("model", model, sm.GetProgram());
	shaders[0]->SetUniformMat4f("view", view, sm.GetProgram());
	shaders[0]->SetUniformMat4f("projection", proj, sm.GetProgram());*/
	shaders[0]->SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
	texture->Bind();
	shaders[1]->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f, sm.GetProgram());
	shaders[1]->SetUniform1i("u_texture", 0, sm.GetProgram());
}
