#pragma once

#include <functional>
#include <string>
#include <vector>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

#include "typewritter.h"

enum class DialogMode {
    // "I want to eat..." 
    // There are no answer choices here, but the same dialogue menu used by NPCs is employed.
    // Pointer in center of the menu
   Mind,


   // "Do you want to eat?"
   // There are we can have answer choices, but dialogue menu position in center
   // Pointer in center of the menu
   
   // Transparent background

   // Using in main character talks (red words) or system messages
   StoryCenter,


   // "He want to eat more..."
   // Response options and the dialogue menu are displayed here, at the bottom of the screen.
   // Without background
   // Pointer in center of the menu

   // Transparent background

   // Using in main character talks or system messages
   StoryDown, 


   // "Shut up..."
   // Classic npc dialogue menu.
   // Pointer in center of the menu
   // With portrait
   Npc
};

struct DialogChoice {
    std::string text;
    std::function<void()> onSelect;
};

class Dialog {
public:
    // plain line(s), no portrait, no answer choices
    void Show(std::string text, DialogMode mode, std::function<void()> onClose = nullptr, Color textColor = WHITE);
    void Show(std::vector<std::string> lines, DialogMode mode, std::function<void()> onClose = nullptr, Color textColor = WHITE);

    // Npc portrait (works with any mode, but really only makes sense for Mind/Npc)
    void ShowWithPortrait(std::vector<std::string> lines, DialogMode mode, TextureResource* portrait, std::function<void()> onClose = nullptr, Color textColor = WHITE);

    // once the lines finish typing, shows a selectable answer menu instead of just closing
    void ShowChoice(std::vector<std::string> lines, DialogMode mode, std::vector<DialogChoice> choices, TextureResource* portrait = nullptr, Color textColor = WHITE);

    void Update(float dt);
    void Draw();

    static void Init();

    bool IsOpen() const { return _visible; }

private:
    void ShowInternal(std::vector<std::string> lines, DialogMode mode, TextureResource* portrait, std::vector<DialogChoice> choices, Color textColor, std::function<void()> onClose);

    void SelectAnswer(int32_t index);

    Rectangle GetBoxRect() const;
    void DrawBox();
    void DrawChoices();
    void DrawContinueHint();

    bool _visible = false;
    DialogMode _mode = DialogMode::StoryCenter;

    TextureResource* _portrait = nullptr;

    std::vector<DialogChoice> _choices;
    int32_t _selectedChoice = 0;
    bool _showingChoices = false;

    std::function<void()> _onClose;

    // Story dim overlay, shared by StoryCenter/StoryDown
    static TextureResource _storyTexture;
    static SpriteV2 _storyBackground;

    // cyrillic-capable font, used by all box/text drawing here (Text::_font is ascii-only)
    static Font _font;

    Typewritter _typewritter;
};
