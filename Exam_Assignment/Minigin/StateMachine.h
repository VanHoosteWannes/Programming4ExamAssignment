#pragma once

//STATE MACHINE BASED OFF THE GAMEPLAY PROGRAMMING STATE MACHINE

namespace dae {
	class Action {
	public:
		virtual void Invoke() = 0;
	};

	class Condition {
	public:
		virtual bool Invoke() = 0;
	};

	class Action;
	class Transition;
	class State final
	{
	public:
		State() = default;
		virtual ~State()
		{
			m_EntryActions.clear();
			m_Actions.clear();
			m_ExitActions.clear();
			m_Transitions.clear();
		}

		//--- Run Actions ---
		void RunActions() const { for (auto a : m_Actions) a->Invoke(); }; //The actions that should run when active
		void RunEntryActions() const { for (auto a : m_EntryActions) a->Invoke(); }; //The action that should run when entering this state
		void RunExitActions() const { for (auto a : m_ExitActions) a->Invoke(); }; //The action that should run when exiting this state

		//--- Setters ---
		void AddEntryActions(Action* entryAction)
		{
			m_EntryActions.push_back(entryAction);
		}
		void AddActions(Action* action)
		{
			m_Actions.push_back(action);
		}
		void AddExitActions(Action* exitAction)
		{
			m_ExitActions.push_back(exitAction);
		}
		void AddTransition(Transition* transition)
		{
			m_Transitions.push_back(transition);
		}

		//--- Getters ---
		std::vector<Transition*> GetTransitions() { return m_Transitions; };

	private:
		//--- Datamembers ---
		std::vector<Action*> m_EntryActions = {};
		std::vector<Action*> m_Actions = {};
		std::vector<Action*> m_ExitActions = {};
		std::vector<Transition*> m_Transitions = {};
	};

	class Transition final
	{
	public:
		//--- Constructor & Destructor ---
		Transition(Condition* condition, Action* action, State* targetState) :
			m_TargetState(targetState), m_Condition(condition), m_Action(action) {}
		Transition()
		{
			m_Condition = {};
			m_Action = {};
		}

		//--- Functions ---
		bool IsTriggered() const //Triggered when one of the given conditions is true
		{
			auto r = false;
			if (m_Condition != nullptr)
			{
				r |= m_Condition->Invoke();
			}
			else
				r = true;
			return r;
		};
		void RunActions() const { m_Action->Invoke(); };

		//--- Getters ---
		State* GetTargetState() const { return m_TargetState; };

		//--- Setters ---
		void SetTargetState(State* state)
		{
			m_TargetState = state;
		}
		void SetCondition(Condition* conditions)
		{
			m_Condition = conditions;
		}
		void SetAction(Action* actions)
		{
			m_Action = actions;
		}

	private:
	    State* m_TargetState = {};
		Condition* m_Condition = {};
		Action* m_Action = {};
	};

	class StateMachine
	{
	public:
		StateMachine(std::vector<State*> states, State* initialState) :
			m_States(states), m_InitialState(initialState), m_CurrentState(initialState) {}
		virtual ~StateMachine()
		{
			m_States.clear();
		}

		//--- Functions ---
		void Start();
		void Update();

	private:
		std::vector<State*> m_States = {};
		State* m_InitialState = {};
		State* m_CurrentState = {};
	};
}

