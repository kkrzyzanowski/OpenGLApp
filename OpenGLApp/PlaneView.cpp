#include "PlaneView.h"
float planeViewQuad[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f };
unsigned int planeViewIndexes[] = { 0, 1, 2,
					3, 4, 5 };

unsigned int planeViewVertexSize = 6;
unsigned int planeViewIndexSize = 6;
unsigned short planeViewBufferDataSize = 4;

PlaneView::PlaneView()  
    : bm(nullptr), sm(nullptr) // Initialize pointers to nullptr  
{  
    // Constructor implementation  
}  

PlaneView::PlaneView(std::vector<Texture*>& textures, std::vector<Shader*>& shaders)  
{  
	bm = std::unique_ptr<BufferManager>(new BufferManager());
	sm = new ShaderManager();
	tm = new TextureManager();
	AddTextures(textures);
	AddShaders(shaders);

	// Initialize the buffers for screen coordinates  
	InitializeBufferScreenCoords();  
	// Set the textures for the plane view  
}

PlaneView::~PlaneView()  
{  
	delete sm;
	delete tm;
}
void PlaneView::AddDefaultShaders()
{
}
void PlaneView::InitializeBufferScreenCoords()
{
	unsigned int bufferDataSizes[2] = { 2, 2 };
	bm->CreateBuffers(planeViewQuad, planeViewIndexes, planeViewVertexSize, planeViewIndexSize, bufferDataSizes, planeViewBufferDataSize);
}

void PlaneView::AddTextures(std::vector<Texture*>& textures)
{
	tm->AddTextures(textures);
}

void PlaneView::SetFunction(ShaderFunction func)
{
	this->func = func;
}

Texture* PlaneView::GetTexture(unsigned int index)
{
	return tm->GetTexture(index);
}

Shader* PlaneView::GetShader(unsigned int index)
{
	return sm->GetShader(index);
}

void PlaneView::AddShaders(std::vector<Shader*>& shaders)
{
	sm->AddShaders(shaders);
	sc.AddShadersToProgram(sm->shaders);
}


void PlaneView::AddParams(std::initializer_list<ShaderParams> newParams)
{
    params.insert(params.end(), newParams.begin(), newParams.end());
}
void PlaneView::UpdateData()
{
	sc.ActivateDefaultProgram();
	
	sc.EnableUse();
	func(sm->shaders, sc.GetCurrentProgram(), params);
	bm->BindBuffers();
}

void PlaneView::AfterUpdate()
{
	for(auto& texture : tm->Textures) {
		texture->UnBind();
	}
}