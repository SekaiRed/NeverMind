#pragma once

#include <stack>
#include "./States/State.hpp"

class State;
//class Engine::State;
namespace Engine
{
    class State;
    //class Engine::State;

    typedef std::unique_ptr<State> StateRef;

    class StateMachine
    {

    private:
        std::stack<Engine::StateRef> _states;
        Engine::StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;

    public:
        StateMachine()
        {
        }
        ~StateMachine()
        {
        }

        void addState(StateRef newState, bool isReplacing);
        void removeState();
        void processStates();

        StateRef &getActiveState();
    };
}