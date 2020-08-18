#pragma once

#include "../graphics/gui/color.h"
#include "../engine/layer/layer.h"
#include "../engine/layer/layerStack.h"

namespace P3D::Graphics {
class ShaderResource;
struct ShaderStage;
class Texture;
class Font;
}

namespace P3D::Engine {
class Node;
}

class Resource;

namespace P3D::Application {

struct BigFrame {
public:
	// PropertiesFrame
	static float position[3];

	// DebugFrame
	static bool renderSpheres;

	// EnvironmentFrame
	static float hdr;
	static float gamma;
	static float exposure;
	static Color3 sunColor;

	// LayerFrame
	static bool doEvents;
	static bool noRender;
	static bool doUpdate;
	static bool isDisabled;
	static Engine::Layer* selectedLayer;

	// ResourceFrame
	static Resource* selectedResource;

private:
	static void renderECSNode(Engine::Node* node);
	static void renderShaderStageInfo(Graphics::ShaderResource* shader, const Graphics::ShaderStage& stage);
	static void renderTextureInfo(Graphics::Texture* texture);
	static void renderFontInfo(Graphics::Font* font);
	static void renderShaderInfo(Graphics::ShaderResource* shader);
	
	static void renderECSTree();
	static void renderPropertiesFrame();
	static void renderDebugFrame();
	static void renderEnvironmentFrame();
	static void renderLayerFrame();
	static void renderResourceFrame();

public:
	static void onInit();
	static void render();

};

};