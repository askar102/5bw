#pragma once

#include <functional>
#include <string>
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "gui.h"


class Button : public Gui {
    public:
        Button();  // в конструкторе берём GuiButton из ResourceManager
        Button(Vector2 pos, Vector2 size, std::string label, std::function<void()> onClick);    


        void SetLabel(const std::string& text);
        void SetOnClick(std::function<void()> callback);
        
        void Update();  // проверяет мышку
        void Draw() override;
    
    private:
        std::string _label;
        std::function<void()> _onClick;
};
