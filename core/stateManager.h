/**
 * @file stateManager.h
 * @author askar102
 * @brief State manager, fully manage states
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #pragma once

 #include <memory>
 
 #include "state.h"
 
 class StateManager {
 public:
     void ChangeState(std::unique_ptr<State> newState);
 
     void HandleInput();
     void Update(float dt);
     void Draw();
 
 private:
     std::unique_ptr<State> currentState;
 };