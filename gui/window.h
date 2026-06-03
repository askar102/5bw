#pragma once

#include <functional>
#include <string>
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "gui.h"

#include "button.h"

class Window : public Gui {
    public:
        Window();
        
        Window(Vector2 pos, Vector2 size, TextureResource* resource, Button& exitButton, std::function<void()> onEnter);
};