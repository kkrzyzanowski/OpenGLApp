#include "..\Builders\LightBuilder.h"
#include "..\Shaders\ShaderClasses\ShaderTypeGenerator.h"

Light::Light()
{
	bm = new BufferManager();
	sc = new ShaderCompiler();
	sm = new ShaderManager();
	lsm = new ShaderManager();
	mvpManager = new MVPManager();
	Position = glm::vec3(3.0f, 7.0f, -2.0f);
	LightProjection = glm::ortho(-ortographicSize, ortographicSize, -ortographicSize, ortographicSize, nearPlane, farPlane);
	LightView = glm::lookAt(Position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	LightSpaceMatrix = LightProjection * LightView;
	params.push_back(LightSpaceMatrix);
	CreateModel();
}

Light::Light(LightBuilder& builder): Position(builder.Pos), nearPlane(builder.NearPlane), farPlane(builder.FarPlane), color(builder.Color), ortographicSize(builder.Size)
{
	bm = new BufferManager();
	sc = new ShaderCompiler();
	sm = new ShaderManager();
	mvpManager = new MVPManager();
	GenerateLightShape();
	LightProjection = glm::ortho(-ortographicSize, ortographicSize, -ortographicSize, ortographicSize, nearPlane, farPlane);
	glm::vec3 sceneCenter = glm::vec3(0.0f);
	LightView = glm::lookAt(Position, sceneCenter, glm::vec3(0.0f, 0.0f, 1.0f));
	LightSpaceMatrix = LightProjection * LightView;
	params.push_back(LightSpaceMatrix);
	CreateModel();

}

void Light::Create(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int dataSize)
{
	unsigned int bufferDataSizes[1] = { 3 };
 	bm->CreateBuffers(points, orderIndex, countVertices, countIndexes, bufferDataSizes, dataSize);
}

void Light::Update()
{
	sc->EnableUse();
	ShaderTypeGenerator::UpdateModel(sm->shaders, sc->GetDefaultProgram(), mvpManager->mvp.model);
	bm->BindBuffers();
}

void Light::GenerateLightShaders()
{
	LoadLightShaders();
	sc->AddShadersToProgram(sm->shaders);
	sc->EnableUse();
	sc->BindBlockData("Matrices");
	ShaderTypeGenerator::UpdateModel(sm->shaders, sc->GetDefaultProgram(), mvpManager->mvp.model);
	ShaderTypeGenerator::UpdateColor(sm->shaders, sc->GetDefaultProgram(), color);
	sc->DisableUse();
	bm->UnbindBuffers();
}

void Light::GenerateMVPLight(Camera* camera)
{
	mvpManager->ApplyProjectionMatrix(camera->GetView());
	mvpManager->ApplyProjectionMatrix(camera->GetProjection());
	mvpManager->SetEyeCamPos(camera->GetCamPos());
}

void Light::CreateModel()
{
	mvpManager->mvp.model = glm::mat4(1.0f);
	mvpManager->mvp.model = glm::translate(mvpManager->mvp.model, Position);
}

void Light::LoadLightShaders()
{
	sm->shaders.push_back(new Shader(PRIMITIVE_VERT_PATH));
	sm->shaders.push_back(new Shader(PRIMITIVE_FRAG_PATH));
}

Light::~Light()
{
	delete lightSphere;
	delete sc;
	delete bm;
	delete sm;
	delete lsm;
}

void Light::GenerateLightShape()
{
	lightSphere = CreateSphere(32, 16, 3, 1.0f);
	Create(lightSphere->Points, lightSphere->Indexes, lightSphere->PointsCount, lightSphere->IndexesCount, 3);
}
