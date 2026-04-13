#pragma once

#include "state.h"
#include "stateMachine.h"
#include <memory>

class Game {
public:
    Game(int width, int height, const char* title);
    ~Game();

    void Run();

    void ChangeState(std::unique_ptr<State> newState);

private:
    void Init();
    void Update();
    void Draw();
    void Shutdown();

private:
    int screenWidth;
    int screenHeight;
    const char* windowTitle;

    bool running;

    StateMachine stateMachine;
};