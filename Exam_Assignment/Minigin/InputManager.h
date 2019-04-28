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

	class InputBase {
	public:
		virtual ~InputBase() = default;
		virtual bool ProcessInput(int) = 0;
		virtual bool IsPressed(const ControllerButton& button) const = 0;
		virtual std::shared_ptr<Command> HandleInput() = 0 ;
		virtual void SetCommandToButton(const std::shared_ptr<Command>& command, const ControllerButton& button) = 0;
	};

	class NullInput : public InputBase { //used to create empty input if gamemode is not coop or versus
		bool ProcessInput(int) override{ return false; }
		bool IsPressed(const ControllerButton&) const override { return false; }
		std::shared_ptr<Command> HandleInput() override { return nullptr; }
		void SetCommandToButton(const std::shared_ptr<Command>&, const ControllerButton&) override{};
	};

	class Input : public InputBase {
	public:
		bool ProcessInput(int i) override;
		bool IsPressed(const ControllerButton& button) const override;
		std::shared_ptr<Command> HandleInput() override;
		void SetCommandToButton(const std::shared_ptr<Command>& command, const ControllerButton& button) override;
	private:
		XINPUT_STATE currentState{};
		std::shared_ptr<Command> CommandA = std::make_shared<ShootCommand>();
		std::shared_ptr<Command> CommandRight = std::make_shared<MoveRightCommand>();
		std::shared_ptr<Command> CommandLeft = std::make_shared<MoveLeftCommand>();
		std::shared_ptr<Command> CommandUp = std::make_shared<MoveUpCommand>();
		std::shared_ptr<Command> CommandDown = std::make_shared<MoveDownCommand>();
	};

	//class InputManager final : public Singleton<InputManager>
	//{
	//public:
	//	bool ProcessInput();
	//	bool IsPressed(const ControllerButton& button) const;
	//	std::shared_ptr<Command> HandleInput();
	//	void SetCommandToButton(const std::shared_ptr<Command>& command, const ControllerButton& button);
	//private:
	//	XINPUT_STATE currentState{};
	//	std::shared_ptr<Command> CommandA = std::make_shared<ShootCommand>();
	//	std::shared_ptr<Command> CommandRight = std::make_shared<MoveRightCommand>();
	//	std::shared_ptr<Command> CommandLeft = std::make_shared<MoveLeftCommand>();
	//	std::shared_ptr<Command> CommandUp = std::make_shared<MoveUpCommand>();
	//	std::shared_ptr<Command> CommandDown = std::make_shared<MoveDownCommand>();
	//};

}
