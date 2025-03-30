#pragma once

enum  ShapeType
{
	TRIANGLE, PLANE, CUBE, SPEHERE, SKYBOX, LINE, TERRAIN, CUSTOM
};
enum LightType
{
	DEFAULT = 0,
	DIRECTIONAL = 1,
	POINT = 2,
	SPOTLIGHT = 3,
	NONELIGHT = 4,
};

enum SourceShapeType
{
	SHAPE = 0,
	LIGHT = 1,
	PARTICLE = 2,
	PRIMITIVE = 3,
	NO_TYPE
};

enum Shading
{
	FORWARD_SHADING = 0,
	DEFFERED_SHADING = 1,
	ONLY_COLOR = 2,
	TEXTURE_COLOR = 3,
	DISPLACEMENT = 4,
	CUBEMAP = 5,
	HDR_SHADING = 6
}; // by bytes to-do

enum class CamView
{
	STATIC = 0, DYNAMIC = 1, MOVABLE = 2
};

enum class ShapeState
{
	CREATING, EXISTING, NOT_EXISTING
};

enum Direction
{
	UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD
};
enum FrameBufferType
{
	POSTPROCESSING = 0, BLUR = 1, HDR = 2, DEPTHMAP = 3, GBUFFER = 4, GAUUSIAN_HORIZONTAL = 5, GAUSSIAN_VERTICAL = 6, BASE = 7
};