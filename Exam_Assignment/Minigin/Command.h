#pragma once
//#include <iostream>
#include "GameObject.h"
#include "MovementComponent.h"

namespace dae {
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(std::shared_ptr<GameObject>& object) = 0;
	};

	class ShootCommand : public Command
	{
	public:
		void Shoot() {
			std::cout << "You shot!\n";
		};
		virtual void Execute(std::shared_ptr<GameObject>&)
		{
		}
	};

	class MoveRightCommand : public Command {
	public:
		virtual void Execute(std::shared_ptr<GameObject>& object)
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveRight();
			}
		}
	};
	class MoveLeftCommand : public Command {
	public:
		virtual void Execute(std::shared_ptr<GameObject>& object)
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveLeft();
			}
		}
	};

	class MoveUpCommand : public Command {
	public:
		virtual void Execute(std::shared_ptr<GameObject>& object)
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveUp();
			}
		}
	};

	class MoveDownCommand : public Command {
	public:
		virtual void Execute(std::shared_ptr<GameObject>& object)
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveDown();
			}
		}
	};
}