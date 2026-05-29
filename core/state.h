/**
 * @file state.h
 * @author askar102
 * @brief Basic state template
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #pragma once

 class StateManager;
 
 class State {
 public:
     virtual ~State() = default;
 
     // start & stop things
     virtual void OnEnter() {}
     virtual void OnExit() {}
    
     virtual void OnPause()  {}
     virtual void OnResume() {}

     // input
     virtual void HandleInput() = 0;
 
     // logic & draw
     virtual void Update(float dt) = 0;
     virtual void Draw() = 0;
 
     void SetStateMachine(StateManager* sm) 
     {
         stateMachine = sm;
     }
 
 protected:
     StateManager* stateMachine = nullptr;
 };