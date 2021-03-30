#pragma once
#include "../engine/InputHandler.h"


namespace Input {
class InputHandlerGl : public InputHandler {
	void ProcessInput(float delta) const override;
};
} // namespace Input
