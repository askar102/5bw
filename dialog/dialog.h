#pragma once

#include <functional>
#include <string>
#include <vector>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"

class Dialog {
    void Show(int id, std::function<void()> onClose = nullptr);

    void Update(float dt);
    void Draw();

    // bool IsOpen() const { return _open; }
};