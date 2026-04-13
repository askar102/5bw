#pragma once

#include "state.h"
#include <memory>

class StateMachine {
public:
    void ChangeState(std::unique_ptr<State> newState);

    void HandleInput();
    void Update(float dt);
    void Draw();



private:
    std::unique_ptr<State> currentState;
};