#include "stateMachine.h"
#include "state.h"

void StateMachine::ChangeState(std::unique_ptr<State> newState) {
    if (currentState) {
        currentState->OnExit();
    }

    currentState = std::move(newState);

    if (currentState) {
        currentState->OnEnter();
    }
}

void StateMachine::HandleInput() {
    if (currentState) {
        currentState->HandleInput();
    }
}

void StateMachine::Update(float dt) {
    if (currentState) {
        currentState->Update(dt);
    }
}

void StateMachine::Draw() {
    if (currentState) {
        currentState->Draw();
    }
}
