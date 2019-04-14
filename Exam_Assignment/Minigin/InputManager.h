#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		std::shared_ptr<Command> HandleInput();
	private:
		XINPUT_STATE currentState{};
		std::shared_ptr<ShootCommand> Shoot = std::make_shared<ShootCommand>();
		std::shared_ptr<MoveRightCommand> MoveRight = std::make_shared<MoveRightCommand>();
		std::shared_ptr<MoveLeftCommand> MoveLeft = std::make_shared<MoveLeftCommand>();
		std::shared_ptr<MoveUpCommand> MoveUp = std::make_shared<MoveUpCommand>();
		std::shared_ptr<MoveDownCommand> MoveDown = std::make_shared<MoveDownCommand>();

		XINPUT_GAMEPAD controller{};
	};

}
