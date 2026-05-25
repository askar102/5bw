/**
 * @file stateManager.cpp
 * @author askar102
 * @brief State manager, fully manage states
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #include "stateManager.h"

 void StateManager::ChangeState(std::unique_ptr<State> newState) 
 {
     if (dispatchingState)
     {
         pendingState = std::move(newState);
         return;
     }

     ApplyStateChange(std::move(newState));
 }

 void StateManager::ApplyStateChange(std::unique_ptr<State> newState)
 {
     if (currentState) 
     {
         currentState->OnExit();
     }
 
     if (newState) 
     {
         newState->SetStateMachine(this);
     }
 
     currentState = std::move(newState);
 
     if (currentState) 
     {   
         currentState->OnEnter();
     }
 }

 void StateManager::ApplyPendingState()
 {
     if (pendingState)
     {
         ApplyStateChange(std::move(pendingState));
     }
 }
 
 void StateManager::HandleInput() 
 {
     if (currentState) 
     {
         dispatchingState = true;
         currentState->HandleInput();
         dispatchingState = false;
         ApplyPendingState();
     }
 }
 
 void StateManager::Update(float dt) 
 {
     if (currentState) 
     {
         dispatchingState = true;
         currentState->Update(dt);
         dispatchingState = false;
         ApplyPendingState();
     }
 }
 
 void StateManager::Draw() 
 {
     if (currentState) 
     {
         currentState->Draw();
     }
 }
 
