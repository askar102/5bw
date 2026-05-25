#pragma once

#include <vector>
#include <memory>

#include "gui.h"
#include "button.h"

class ButtonList : public Gui {
public:
    void Draw() override; // становяться в ряд
    void Update() override;

    void Add(std::unique_ptr<Button> newButton);

    void Clear();

    int GetSelectedIndex() const { return _selectedIndex; }

private:
    std::vector<std::unique_ptr<Button>> _buttons;

    int _selectedIndex = 0;

    static constexpr float SPACING     = 30.0f;
    static constexpr int   CURSOR_SIZE = 6;
};