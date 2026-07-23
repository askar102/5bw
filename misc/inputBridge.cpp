#include "inputBridge.h"

#include <unordered_set>
#include <unordered_map>

namespace {
    std::unordered_set<int> forcedDown;
    std::unordered_map<int, bool> tapPending;

    bool clickPending[8] = { false };

    bool hasForcedMouse = false;
    Vector2 forcedMouse = { 0, 0 };
}

namespace InputBridge {

bool KeyDown(int key) {
    return IsKeyDown(key) || forcedDown.count(key) > 0;
}

bool KeyPressed(int key) {
    if (IsKeyPressed(key)) return true;
    auto it = tapPending.find(key);
    return it != tapPending.end() && it->second;
}

bool MouseButtonPressed(int button) {
    if (IsMouseButtonPressed(button)) return true;
    return button >= 0 && button < 8 && clickPending[button];
}

Vector2 OverrideWorldMouse(Vector2 realWorldMouse) {
    return hasForcedMouse ? forcedMouse : realWorldMouse;
}

void EndFrame() {
    hasForcedMouse = false;
    tapPending.clear();
    for (bool& pending : clickPending) pending = false;
}

void ForceKeyDown(int key) { forcedDown.insert(key); }
void ForceKeyUp(int key)   { forcedDown.erase(key); }
void ForceTapKey(int key)  { tapPending[key] = true; }

void ForceClickAt(float worldX, float worldY) {
    hasForcedMouse = true;
    forcedMouse = { worldX, worldY };
    clickPending[MOUSE_LEFT_BUTTON] = true;
}

}

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE void TestApi_KeyDown(int key) { InputBridge::ForceKeyDown(key); }
    EMSCRIPTEN_KEEPALIVE void TestApi_KeyUp(int key)    { InputBridge::ForceKeyUp(key); }
    EMSCRIPTEN_KEEPALIVE void TestApi_TapKey(int key)   { InputBridge::ForceTapKey(key); }
    EMSCRIPTEN_KEEPALIVE void TestApi_ClickAt(float x, float y) { InputBridge::ForceClickAt(x, y); }
}
#endif
