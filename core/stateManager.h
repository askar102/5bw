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

 #include <vector>
 #include <memory>
 
 #include "state.h"
 
 class StateManager {
 public:
     void ChangeState(std::unique_ptr<State> newState);

     void PushState(std::unique_ptr<State> newState);
     void PopState();
 
     void HandleInput();
     void Update(float dt);
     void Draw();

     bool IsEmpty() const { return _stack.empty(); }
     int  StackSize() const { return static_cast<int>(_stack.size()); }
 
 private:
    void ApplyPending();

    void DoChange(std::unique_ptr<State> newState);
    void DoPush  (std::unique_ptr<State> newState);
    void DoPop   ();

    State* Top() const;

    std::vector<std::unique_ptr<State>> _stack;
    bool _dispatching = false;

    enum class PendingKind { None, Change, Push, Pop };

    struct PendingCmd {
        PendingKind              kind = PendingKind::None;
        std::unique_ptr<State>   state; 
    };

    PendingCmd _pending;
 };
