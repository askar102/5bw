#pragma once

#include <functional>
#include <string>
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "gui.h"


enum class PositionType {
    Center,
    Left,
    Right
};

class Button : public Gui {
    public:
        Button(); 
        // default with non-custom rsource
        Button(Vector2 pos, Vector2 size, std::string label, std::function<void()> onClick, PositionType textPositionType = PositionType::Center);
        // with custom resource
        Button(Vector2 pos, Vector2 size, std::string label, TextureResource* resource, std::function<void()> onClick, PositionType textPositionType = PositionType::Center);  
        // with onTouch 
        Button(Vector2 pos, Vector2 size, std::string label, TextureResource* resource, std::function<void()> onClick, std::function<void()> onTouch, PositionType textPositionType = PositionType::Center);

        void SetLabel(const std::string& text);
        void SetOnClick(std::function<void()> callback);
        void SetOnTouch(std::function<void()> callback);

        void UseOnClick();
        void UseOnTouch();

        void SetTextColor(Color newColor = WHITE);
        void SetTextPositionType(PositionType newType);
        
        void Update() override;  // проверяет мышку
        void Draw() override;
    
    private:
        std::string _label;
        std::function<void()> _onClick;
        std::function<void()> _onTouch;

        Color _textColor = WHITE;
        int _textFontSize = 16;
        PositionType _textPositionType = PositionType::Center;
};
