#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include "ButtonComponent.h"
#include "DigDugWeaponComponent.h"

namespace dae {

	class MoveRightCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveRight();
			}
		}
	};
	class MoveLeftCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveLeft();
			}
		}
	};

	class MoveUpCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveUp();
			}
		}
	};

	class MoveDownCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveDown();
			}
		}
	};

	class ButtonActivateCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override {
			if (object->HasComponent<ButtonComponent>()) {
				object->GetComponent<ButtonComponent>()->Activate();
			}
		}
	};

	class ShootCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override {
			if (object->HasComponent<DigDugWeaponComponent>()) {
				object->GetComponent<DigDugWeaponComponent>()->Activate();
			}
		}
	};
}
