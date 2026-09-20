#pragma once
#include "Builder.h"
#include "../TextureObjects/Texture.h"
#include "../Shaders/ShaderClasses/Shader.h"
#include "../Shaders/ShaderClasses/ShaderTypeGenerator.h"

namespace AppEngine
{
	class FrameBuffer;

	class FrameBufferBuilder :public Builder<FrameBuffer, FrameBufferType>
	{
	public:
		FrameBufferBuilder() = default;
		FrameBufferBuilder(FrameBufferBuilder&& other) noexcept;
		FrameBufferBuilder(FrameBufferBuilder& other) noexcept;
		FrameBufferBuilder(const FrameBufferBuilder& other) noexcept;
		FrameBufferBuilder& operator=(FrameBufferBuilder&& other) noexcept;
		FrameBufferBuilder& operator=(FrameBufferBuilder& other) noexcept;
		FrameBufferBuilder& AddShaderByPath(const char* path);
		FrameBufferBuilder& AddShaderByPath(const std::string& path);
		FrameBufferBuilder& AddShaders(std::vector<Shader*>& shaders);
		FrameBufferBuilder& AddShaders(std::vector<Shader*>&& shaders);
		FrameBufferBuilder& AddTexture(TextureMode mode, unsigned int width, unsigned int height, unsigned short slot = 0, unsigned short colorAttachment = 0);
		FrameBufferBuilder& Name(const char* name);
		FrameBufferBuilder& RenderTarget(unsigned int renderTargetFBO);
		FrameBufferBuilder& Size(glm::vec2 size);
		std::shared_ptr<FrameBuffer> Create(const FrameBufferType frameBufferType) override;
		void ResetData();


		std::vector<const char*> ShaderPaths;
		std::vector<Texture*> textures;
		std::vector<Shader*> shaders;
		char* name;
		unsigned int renderTargetFBO;
		glm::vec2 size;
		ShaderFunction func;
		FrameBufferType type = POSTPROCESSING;
		~FrameBufferBuilder() = default;
	};
}
