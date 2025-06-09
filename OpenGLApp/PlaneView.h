#pragma once
#include "Shaders/ShaderClasses/ShaderManager.h"
#include "Managers/TextureManager.h"
#include "Managers/ShaderCompiler.h"
#include "Managers/BufferManager.h"
class PlaneView  
{  
public:  
    PlaneView();
    PlaneView(std::vector<Texture*>& textures, std::vector<Shader*>& shaders);
    ~PlaneView(); 
	void AddDefaultShaders();
    void AddShaders(const std::vector<const char*>& paths);  
    void AddShaders(std::vector<Shader*>& shaders);
    void AddParams(std::initializer_list<ShaderParams> newParams);
    void UpdateData();
    void AfterUpdate();
    void AddTextures(const std::vector<const char*>& paths);  
    void AddTextures(std::vector<Texture*>& textures);  
	void SetFunction(ShaderFunction func);
    Texture* GetTexture(unsigned int index = 0);  
    Shader* GetShader(unsigned int index = 0);  

private:  
    void InitializeBufferScreenCoords(); 
    TextureManager* tm;  
    ShaderCompiler sc;  
    std::unique_ptr<BufferManager> bm;
    ShaderManager* sm;  
    std::vector<ShaderParams> params;  
    ShaderFunction func;  
};

