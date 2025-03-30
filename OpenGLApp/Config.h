#pragma once
#include <filesystem>

static const unsigned int SCREEN_WIDTH = 1920;
static const unsigned int SCREEN_HEIGHT = 1080;
static const unsigned int SHADOW_WIDTH = 1024; 
static const unsigned int SHADOW_HEIGHT = 1024;


inline std::string GetAssetPath(const std::string& relativePath)
{
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::filesystem::path fullPath = currentPath / relativePath;
	return fullPath.string();
}


/// Paths to shaders

static const char* GBUFFER_VERT_PATH =          "..\\Assets\\Shaders\\GBuffer.vert"											;
static const char* GBUFFER_FRAG_PATH =			"..\\Assets\\Shaders\\GBuffer.frag"											;
static const char* DEFFERED_VERT_PATH =			"..\\Assets\\Shaders\\DefferedShading.vert"									;
static const char* DEFFERED_FRAG_PATH =			"..\\Assets\\Shaders\\DefferedShading.frag"									;
static const char* DIFFUSE_VERT_PATH =			"..\\Assets\\Shaders\\DiffuseVertexShader.vert"								;
static const char* DIFFUSE_FRAG_PATH =			"..\\Assets\\Shaders\\DiffuseFragmentShader.frag"							;
static const char* TERRAIN_VERT_PATH =			"..\\Assets\\Shaders\\TerrainVertexShader.vert"								;
static const char* TERRAIN_FRAG_PATH =			"..\\Assets\\Shaders\\TerrainFragmentShader.frag"							;
static const char* DISPLACEMENT_VERT_PATH =		"..\\Assets\\Shaders\\DisplacementVertexShader.vert"						;
static const char* DISPLACEMENT_FRAG_PATH =		"..\\Assets\\Shaders\\DisplacementFragmentShader.frag"						;
static const char* LIGHT_TEXTURE_VERT_PATH =	"..\\Assets\\Shaders\\LightVertexShader.vert"								;
static const char* LIGHT_TEXTURE_FRAG_PATH =	"..\\Assets\\Shaders\\LightFragmentShader.frag"								;
static const char* CUBEBOX_VERT_PATH =			"..\\Assets\\Shaders\\SimpleShaderCubeBox.vert"								;
static const char* CUBEBOX_FRAG_PATH =			"..\\Assets\\Shaders\\SimpleShaderCubeBox.frag"								;
static const char* PRIMITIVE_VERT_PATH =		"..\\Assets\\Shaders\\PrimitiveVertexShader.vert"							;
static const char* PRIMITIVE_FRAG_PATH =		"..\\Assets\\Shaders\\PrimitiveFragmentShader.frag"							;
static const char* PICKING_VERT_PATH =			"..\\Assets\\Shaders\\PickingVertexShader.vert"								;
static const char* PICKING_FRAG_PATH =			"..\\Assets\\Shaders\\PickingFragmentShader.frag"							;
static const char* SHADOW_VERT_PATH =			"..\\Assets\\Shaders\\LightShadow.vert"										;
static const char* SHADOW_FRAG_PATH =			"..\\Assets\\Shaders\\LightShadow.frag"										;
static const char* POSTPROCESSING_VERT_PATH =	"..\\Assets\\Shaders\\PostProcesingShader.vert"								;
static const char* POSTPROCESSING_FRAG_PATH =	"..\\Assets\\Shaders\\PostProcesingShader.frag"								;
static const char* HDR_VERT_PATH =				"..\\Assets\\Shaders\\HDRShader.vert"										;
static const char* HDR_FRAG_PATH =				"..\\Assets\\Shaders\\HDRShader.frag"										;
static const char* HDR_GAUSSIANBLUR_VERT_PATH =	"..\\Assets\\Shaders\\HDRGaussianBlurShader.vert"							;
static const char* HDR_GAUSSIANBLUR_FRAG_PATH =	"..\\Assets\\Shaders\\HDRGaussianBlurShader.frag"							;
static const char* GAUSSIANBLUR_VERT_PATH =		"..\\Assets\\Shaders\\GaussianBlurShader.vert"								;
static const char* GAUSSIANBLUR_FRAG_PATH =		"..\\Assets\\Shaders\\GaussianBlurShader.frag"								;
static const char* LIGHTNING_HDR_VERT =			"..\\Assets\\Shaders\\LightningHDR.vert"									;
static const char* LIGHTNING_HDR_FRAG =			"..\\Assets\\Shaders\\LightningHDR.frag"									;

static const char* TEMP_TEXTURE_DIFFUSE =		"..\\Assets\\Textures\\BrickMedievalBlocks0129_2_M.jpg"						;
static const char* TEMP_TEXTURE_SPECULAR =		"..\\Assets\\Textures\\BrickMedievalBlocks0129_2_M_specular_map.jpg"			;
static const char* TEMP_TEXTURE_NORMALMAP =		"..\\Assets\\Textures\\BrickMedievalBlocksNormalMap.png"						;
static const char* TEMP_TEXTURE_DISPLACEMENTMAP="..\\Assets\\Textures\\BrickMedievalBlocksDisplacementMap.png"				;
static const char* TEMP_TEXTURE_GRASS =			"..\\Assets\\Textures\\TexturesCom_Grass0130_1_seamless_S.jpg"				;
static const char* TEMP_TEXTURE_METAL_EMMISIVE ="..\\Assets\\Textures\\TexturesCom_Metal_RedHotSteel_1K_emissive.jpg"			;
															
static const char* TEMP_MODEL_PATH =			"..\\Assets\\Models\\Hammer.obj"											;
															
static const char* CUBEBOX_RIGHT_PATH =			"..\\Assets\\Textures\\SkyBox\\Daylight Box_Right.bmp"						;
static const char* CUBEBOX_LEFT_PATH =			"..\\Assets\\Textures\\SkyBox\\Daylight Box_Left.bmp"							;
static const char* CUBEBOX_TOP_PATH =			"..\\Assets\\Textures\\SkyBox\\Daylight Box_Top.bmp"							;
static const char* CUBEBOX_BOTTOM_PATH =		"..\\Assets\\Textures\\SkyBox\\Daylight Box_Bottom.bmp"						;
static const char* CUBEBOX_FRONT_PATH =			"..\\Assets\\Textures\\SkyBox\\Daylight Box_Front.bmp"						;
static const char* CUBEBOX_BACK_PATH =			"..\\Assets\\Textures\\SkyBox\\Daylight Box_Back.bmp"							;


//Effects

static bool SHADOW = true;
static bool POSTPROCESSING_EFFECTS = false;
static bool HDR_LIGHT = false;