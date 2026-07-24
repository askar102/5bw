#pragma once

#include <functional>
#include <string>
#include <memory>
#include <vector>

#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "gui.h"
#include "button.h"

class Window : public Gui {
    public:
        Window(Button* hook, Vector2 pos = {400, 300}, Vector2 size = {410, 297}, std::function<void()> onEnter = nullptr);

        void Update() override;
        void Draw() override;

        void Show(bool value);

        // additional buttons
        void AddButton(std::unique_ptr<Button> newButton);
        // rvalue-referens means that we "steal" vector
        void AddButtons(std::vector<std::unique_ptr<Button>>&& newButtonsVec);

        // any other Gui child (Scroll, etc), ticked/drawn only while window is visible
        Gui* AddElement(std::unique_ptr<Gui> element);

    private:
        // windowBg - is _sprite from Gui class-parent
        // SpriteV2 _windowBg;
        Button _exitButton;

        Vector2 _pos;
        Vector2 _size;
        std::function<void()> _onEnter;

        // hook button
        Button* _hookButton = nullptr;

        // Res
        TextureResource _bgRes;
        TextureResource _exitRes;

        std::vector<std::unique_ptr<Button>> _additionalButtons;
        std::vector<std::unique_ptr<Gui>> _elements;
};