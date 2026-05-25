#pragma once

#include <functional>
#include <string>
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "gui.h"


class Button : public Gui {
    public:
        Button();  // в конструкторе берём GuiButton из ResourceManager
        // default with non-custom rsource
        Button(Vector2 pos, Vector2 size, std::string label, std::function<void()> onClick);
        // with custom resource
        Button(Vector2 pos, Vector2 size, std::string label, TextureResource* resource, std::function<void()> onClick);  
        // with onTouch 
        Button(Vector2 pos, Vector2 size, std::string label, TextureResource* resource, std::function<void()> onClick, std::function<void()> onTouch);

        void SetLabel(const std::string& text);
        void SetOnClick(std::function<void()> callback);
        void SetOnTouch(std::function<void()> callback);
        
        void Update() override;  // проверяет мышку
        void Draw() override;
    
    private:
        std::string _label;
        std::function<void()> _onClick;
        std::function<void()> _onTouch;
};
