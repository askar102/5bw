#pragma once

#include "../raylib/raylib.h"

// Test-only input overlay: lets automated testing (Playwright) inject
// deterministic key/mouse state at the game-logic level instead of
// simulating real DOM/browser events, which turned out to be unreliable
// through the canvas letterbox scaling + real frame timing.
namespace InputBridge {
    bool KeyDown(int key);
    bool KeyPressed(int key);
    bool MouseButtonPressed(int button);

    Vector2 OverrideWorldMouse(Vector2 realWorldMouse);

    // call once per real game frame, after state update
    void EndFrame();

    // injection points, wired to window.TestAPI in the web build
    void ForceKeyDown(int key);
    void ForceKeyUp(int key);
    void ForceTapKey(int key);
    void ForceClickAt(float worldX, float worldY);
}
