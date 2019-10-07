#include "core.h"

#include "standardInputHandler.h"

#include "keyboard.h"
#include "mouse.h"

#include "../application/worldBuilder.h"
#include "../options/keyboardOptions.h"
#include "../view/renderUtils.h"
#include "../engine/math/mathUtil.h"
#include "../application.h"
#include "../view/picker/picker.h"
#include "../view/gui/gui.h"
#include "../view/gui/guiUtils.h"
#include "../view/debug/visualDebug.h"
#include "../worlds.h"
#include "../view/screen.h"
#include "../view/camera.h"
#include <random>

StandardInputHandler::StandardInputHandler(GLFWwindow* window, Screen& screen) : InputHandler(window), screen(screen) {}

void StandardInputHandler::onEvent(Event& event) {
	screen.onEvent(event);

	EventDispatcher dispatcher(event);

	if (dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_METHOD(StandardInputHandler::onKeyPress)))
		return;	

	if (dispatcher.dispatch<DoubleKeyPressEvent>(BIND_EVENT_METHOD(StandardInputHandler::onDoubleKeyPress)))
		return;

	if (dispatcher.dispatch<FrameBufferResizeEvent>(BIND_EVENT_METHOD(StandardInputHandler::onFrameBufferResize)))
		return;

}

bool StandardInputHandler::onFrameBufferResize(FrameBufferResizeEvent& event) {
	Vec2i dimension = Vec2i(event.getWidth(), event.getHeight());

	Renderer::viewport(Vec2i(), dimension);

	(*screen.eventHandler.windowResizeHandler) (screen, dimension);

	return true;
}

bool StandardInputHandler::onKeyPressOrRepeat(KeyPressEvent& event) {
	int key = event.getKey();

	if (KeyboardOptions::Tick::Speed::up == key) {
		setSpeed(getSpeed() * 1.5);
		Log::info("TPS is now: %f", getSpeed());
	} else if (KeyboardOptions::Tick::Speed::down == key) {
		setSpeed(getSpeed() / 1.5);
		Log::info("TPS is now: %f", getSpeed());
	} else if (KeyboardOptions::Tick::run == key) {
		if(isPaused()) runTick();
	} else if (Keyboard::O == key) {
		WorldBuilder::createDominoAt(Position(0.0 + (rand() % 100) * 0.001, 1.0 + (rand() % 100) * 0.001, 0.0 + (rand() % 100) * 0.001), fromEulerAngles(0.2, 0.3, 0.7));
		Log::info("Created domino! There are %d objects in the world! ", screen.world->getPartCount());
	}

	return true;
}

bool StandardInputHandler::onKeyPress(KeyPressEvent& event) {
	if (event.isRepeated()) {
		return onKeyPressOrRepeat(event);
	}

	int key = event.getKey();

	if (KeyboardOptions::Tick::pause == key) {
		togglePause();
	} else if (KeyboardOptions::Part::remove == key) {
		if (screen.selectedPart != nullptr) {
			screen.world->removePart(screen.selectedPart);
			screen.world->selectedPart = nullptr;
			screen.selectedPart = nullptr;
		}
	} else if (KeyboardOptions::Debug::pies == key) {
		Debug::renderPiesEnabled = !Debug::renderPiesEnabled;
	} else if (KeyboardOptions::Part::anchor == key) {
		if (screen.selectedPart != nullptr) {
			if (screen.selectedPart->parent->anchored) {
				screen.selectedPart->parent->setAnchored(false);
			} else {
				Physical* parent = screen.selectedPart->parent;
				parent->velocity = Vec3();
				parent->angularVelocity = Vec3();
				parent->totalForce = Vec3();
				parent->totalMoment = Vec3();
				screen.selectedPart->parent->setAnchored(true);
			}
		}
	} else if (KeyboardOptions::World::valid == key) {
		Log::debug("Checking World::isValid()");
		screen.world->isValid();
	} else if (KeyboardOptions::Edit::rotate == key) {
		Picker::editTools.editMode = EditTools::EditMode::ROTATE;
	} else if (KeyboardOptions::Edit::translate == key) {
		Picker::editTools.editMode = EditTools::EditMode::TRANSLATE;
	} else if (KeyboardOptions::Edit::scale == key) {
		Picker::editTools.editMode = EditTools::EditMode::SCALE;
	} else if (KeyboardOptions::Debug::spheres == key) {
		Debug::colissionSpheresMode = static_cast<Debug::SphereColissionRenderMode>((static_cast<int>(Debug::colissionSpheresMode) + 1) % 3);
	} else if (KeyboardOptions::Debug::tree == key) {
		Debug::colTreeRenderMode = static_cast<Debug::ColTreeRenderMode>((static_cast<int>(Debug::colTreeRenderMode) + 1) % 5);
	}
	

	if(Keyboard::F1 <= key && Keyboard::F9 >= key) {
		toggleVectorType(static_cast<Debug::VectorType>(key - Keyboard::F1.code));
	}
	if (Keyboard::NUMBER_1 <= key && Keyboard::NUMBER_3 >= key) {
		togglePointType(static_cast<Debug::PointType>(key - Keyboard::NUMBER_1.code));
	}

	return true;
};

bool StandardInputHandler::onDoubleKeyPress(DoubleKeyPressEvent& event) {
	int key = event.getKey();

	if (KeyboardOptions::Move::fly == key) {
		toggleFlying();
	}

	return true;
}