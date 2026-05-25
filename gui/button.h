#pragma once

#include <functional>
#include <string>
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "gui.h"


class Button : public Gui {
    public:
        Button();  // в конструкторе берём GuiButton из ResourceManager
        
        void SetLabel(const std::string& text);
        void SetOnClick(std::function<void()> callback);
        
        void Update();  // проверяет мышку
        void Draw() override;
    
    private:
        std::string _label;
        std::function<void()> _onClick;
};
