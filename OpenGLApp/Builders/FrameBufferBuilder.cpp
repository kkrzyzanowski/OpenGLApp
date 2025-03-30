#include "FrameBufferBuilder.h"
#include "..\Buffers\FrameBuffer.h"

FrameBufferBuilder::FrameBufferBuilder(FrameBufferBuilder&& other) noexcept
{
	this->ShaderPaths = std::move(other.ShaderPaths);
	this->func = std::move(other.func);
	this->name = std::move(other.name);
	this->Pos = other.Pos;
	this->color = other.color;
	this->Angle = other.Angle;
	this->Axis = other.Axis;
	this->type = other.type;
}

FrameBufferBuilder::FrameBufferBuilder(FrameBufferBuilder& other) noexcept
{
	if (this != &other)
	{
		this->ShaderPaths = other.ShaderPaths;
		this->Pos = other.Pos;
		this->func = other.func;
		this->color = other.color;
		this->Angle = other.Angle;
		this->Axis = other.Axis;
		this->Type = other.Type;
		this->name = other.name;
		this->type = other.type;
		this->ShaderPaths = other.ShaderPaths;
	}
}

FrameBufferBuilder& FrameBufferBuilder::operator=(FrameBufferBuilder& other) noexcept
{
	// TODO: insert return statement here
	return *this;
}

FrameBufferBuilder& FrameBufferBuilder::AddShaderByPath(const char* path)
{
	ShaderPaths.push_back(path);
	return *this;
}

FrameBufferBuilder& FrameBufferBuilder::AddShaderByPath(const std::string& path)
{
	ShaderPaths.push_back(path.c_str());
	return *this;
}

FrameBufferBuilder& FrameBufferBuilder::AddShaders(std::vector<Shader*>& shaders)
{
	this->shaders.insert(this->shaders.end(), shaders.begin(), shaders.end());
	return *this;
}

FrameBufferBuilder& FrameBufferBuilder::AddShaders(std::vector<Shader*>&& shaders)
{
	this->shaders.insert(this->shaders.end(), shaders.begin(), shaders.end());
	return *this;
}


FrameBufferBuilder& FrameBufferBuilder::Name(const char* name)
{
	// TODO: insert return statement here
	return *this;
}

FrameBufferBuilder& FrameBufferBuilder::AddTexture(TextureMode mode)
{
	textures.push_back(new Texture(0, 0, 5126, mode));
	return *this;
}
	

std::shared_ptr<FrameBuffer> FrameBufferBuilder::Create(const FrameBufferType frameBufferType)
{
	this->type = frameBufferType;
	return std::make_shared<FrameBuffer>(*this);
}

void FrameBufferBuilder::ResetData()
{
	this->Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	this->Angle = 0.0f;
	this->Axis = glm::vec3(0.0f, 0.0f, 0.0f);
	this->type = POSTPROCESSING;

	this->ShaderPaths.clear();
	this->textures.clear();
	this->func = nullptr;
	this->name = nullptr;
}
