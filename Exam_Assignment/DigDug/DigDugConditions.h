#pragma once
#include <StateMachine.h>
#include "Locator.h"
#include "CollisionComponent.h"
#include "AIComponent.h"

namespace dae {
	class InflateCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie collides with weapon
			if(Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetColliding() &&
				Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Weapon") {
				return true;
			}
			return false;
		}
	};

	class DeflateCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie doesnt collides with weapon
			if (Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetColliding() &&
				Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Weapon") {
				return false;
			}
			return true;
		}
	};

	class DeadCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie is gonna explode
			if (Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->GetInflateState() == 3) {
				return true;
			}
			return false;
		}
	};

	class IdleCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie is going idle
			if (Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->GetInflateState() == 0) {
				return true;
			}
			return false;
		}
	};

	class RockCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie collides with weapon
			if (Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetColliding() &&
				Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Rock") {
				return true;
			}
			return false;
		}
	};

}

