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
    if (_dispatching)
    {
        _pending.kind  = PendingKind::Change;
        _pending.state = std::move(newState);
        return;
    }
    DoChange(std::move(newState));
}
 
void StateManager::PushState(std::unique_ptr<State> newState)
{
    if (_dispatching)
    {
        _pending.kind  = PendingKind::Push;
        _pending.state = std::move(newState);
        return;
    }
    DoPush(std::move(newState));
}
 
void StateManager::PopState()
{
    if (_dispatching)
    {
        _pending.kind  = PendingKind::Pop;
        _pending.state = nullptr;
        return;
    }
    DoPop();
}

 
void StateManager::HandleInput()
{
    if (State* top = Top())
    {
        _dispatching = true;
        top->HandleInput();
        _dispatching = false;
        ApplyPending();
    }
}
 
void StateManager::Update(float dt)
{
    if (State* top = Top())
    {
        _dispatching = true;
        top->Update(dt);
        _dispatching = false;
        ApplyPending();
    }
}
 
void StateManager::Draw()
{
    // Рисуем весь стек снизу вверх — нижние стейты видны "под" верхними.
    // Если не нужно (например BattleState не должен просвечивать под SceneState) —
    // замени на: if (State* top = Top()) top->Draw();
    for (auto& statePtr : _stack)
        statePtr->Draw();
}


 State* StateManager::Top() const
{
    if (_stack.empty()) return nullptr;
    return _stack.back().get();
}
 
void StateManager::DoChange(std::unique_ptr<State> newState)
{
    // OnExit всему стеку снизу вверх, потом чистим
    for (int i = static_cast<int>(_stack.size()) - 1; i >= 0; --i)
        _stack[i]->OnExit();
 
    _stack.clear();
 
    if (newState)
    {
        newState->SetStateMachine(this);
        _stack.push_back(std::move(newState));
        _stack.back()->OnEnter();
    }
}
 
void StateManager::DoPush(std::unique_ptr<State> newState)
{
    if (!newState) return;
 
    // Текущий верхний стейт уходит на паузу
    if (State* top = Top())
        top->OnPause();
 
    newState->SetStateMachine(this);
    _stack.push_back(std::move(newState));
    _stack.back()->OnEnter();
}
 
void StateManager::DoPop()
{
    if (_stack.empty()) return;
 
    // Снимаем верхний
    _stack.back()->OnExit();
    _stack.pop_back();
 
    // Возобновляем новый верхний
    if (State* top = Top())
        top->OnResume();
}
 
void StateManager::ApplyPending()
{
    if (_pending.kind == PendingKind::None) return;
 
    PendingCmd cmd = std::move(_pending);
    _pending.kind  = PendingKind::None;
 
    switch (cmd.kind)
    {
        case PendingKind::Change: DoChange(std::move(cmd.state)); break;
        case PendingKind::Push:   DoPush  (std::move(cmd.state)); break;
        case PendingKind::Pop:    DoPop   ();                     break;
        default: break;
    }
}
 

 
