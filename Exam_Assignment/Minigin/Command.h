#pragma once
//#include <iostream>
#include "GameObject.h"
#include "MovementComponent.h"
#include "ButtonComponent.h"

namespace dae {
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(std::shared_ptr<GameObject>& object) = 0;
	};

	class ShootCommand final: public Command
	{
	public:
		void Shoot() {
			std::cout << "You shot!\n";
		};
		void Execute(std::shared_ptr<GameObject>&) override
		{
		}
	};

	class MoveRightCommand final: public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveRight();
			}
		}
	};
	class MoveLeftCommand final: public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveLeft();
			}
		}
	};

	class MoveUpCommand final: public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveUp();
			}
		}
	};

	class MoveDownCommand final: public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveDown();
			}
		}
	};

	class ButtonActivateCommand final: public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override{
			if(object->HasComponent<ButtonComponent>()) {
				object->GetComponent<ButtonComponent>()->Activate();
			}
		}
	};
}
