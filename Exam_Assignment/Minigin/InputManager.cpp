#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


//bool dae::InputManager::ProcessInput()
//{
//	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
//	XInputGetState(0, &currentState);
//
//	SDL_Event e;
//	while (SDL_PollEvent(&e)) {
//		if (e.type == SDL_QUIT) {
//			return false;
//		}
//		if (e.type == SDL_KEYDOWN) {
//			
//		}
//		if (e.type == SDL_MOUSEBUTTONDOWN) {
//			
//		}
//	}
//
//	return true;
//}
//
//bool dae::InputManager::IsPressed(const ControllerButton& button) const
//{
//	//switch (button)
//	//{
//	//case ControllerButton::ButtonA:
//	//	return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
//	//case ControllerButton::ButtonB:
//	//	return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
//	//case ControllerButton::ButtonX:
//	//	return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
//	//case ControllerButton::ButtonY:
//	//	return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
//	//default: return false;
//	//}
//
//	bool is_button_pressed = ((currentState.Gamepad.wButtons & int(button)) != 0);
//
//	if (is_button_pressed) {
//		return true;
//	}
//	return false;
//}
//
//std::shared_ptr<dae::Command> dae::InputManager::HandleInput() {
//	if(IsPressed(ControllerButton::ButtonA)) {
//		return CommandA;
//	}
//	if(IsPressed(ControllerButton::ButtonRight)) {
//		return CommandRight;
//	}
//	if (IsPressed(ControllerButton::ButtonLeft)) {
//		return CommandLeft;
//	}
//	if (IsPressed(ControllerButton::ButtonUp)) {
//		return CommandUp;
//	}
//	if (IsPressed(ControllerButton::ButtonDown)) {
//		return CommandDown;
//	}
//	return nullptr;
//}
//
//void dae::InputManager::SetCommandToButton(const std::shared_ptr<Command>& command, const ControllerButton& button) {
//	switch(button) 
//	{
//	case ControllerButton::ButtonA:
//		CommandA = command;
//		break;
//	case ControllerButton::ButtonRight:
//		CommandRight = command;
//		break;
//	case ControllerButton::ButtonLeft:
//		CommandLeft = command;
//		break;
//	case ControllerButton::ButtonUp:
//		CommandUp = command;
//		break;
//	case ControllerButton::ButtonDown:
//		CommandDown = command;
//		break;
//	}
//}

bool dae::Input::ProcessInput(int i) {
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(i, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::Input::IsPressed(const ControllerButton& button) const {

	bool is_button_pressed = ((currentState.Gamepad.wButtons & int(button)) != 0);

	if (is_button_pressed) {
		return true;
	}
	return false;
}

std::shared_ptr<dae::Command> dae::Input::HandleInput() {
	if (IsPressed(ControllerButton::ButtonA)) {
		return CommandA;
	}
	if (IsPressed(ControllerButton::ButtonRight)) {
		return CommandRight;
	}
	if (IsPressed(ControllerButton::ButtonLeft)) {
		return CommandLeft;
	}
	if (IsPressed(ControllerButton::ButtonUp)) {
		return CommandUp;
	}
	if (IsPressed(ControllerButton::ButtonDown)) {
		return CommandDown;
	}
	return nullptr;
}

void dae::Input::SetCommandToButton(const std::shared_ptr<Command>& command, const ControllerButton& button) {
	switch (button)
	{
	case ControllerButton::ButtonA:
		CommandA = command;
		break;
	case ControllerButton::ButtonRight:
		CommandRight = command;
		break;
	case ControllerButton::ButtonLeft:
		CommandLeft = command;
		break;
	case ControllerButton::ButtonUp:
		CommandUp = command;
		break;
	case ControllerButton::ButtonDown:
		CommandDown = command;
		break;
	}
}
