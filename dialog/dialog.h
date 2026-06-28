#pragma once

#include <functional>
#include <string>
#include <vector>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"

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


class Dialog {
public:
    void Show(int id, DialogMode mode, std::function<void()> onClose = nullptr);

    void Update(float dt);
    void Draw();

    static void Init();
    // bool IsOpen() const { return _open; }

private:
    void LoadLine();
    void NextLine();
    void SelectAnswer(int32_t index);
    
    bool _visible = false;
    DialogMode _mode;

    // Story
    static TextureResource _storyTexture;
    static SpriteV2 _storyBackgroud;
    
    // NPC / MIND
    static TextureResource _defaultTexture;
    static SpriteV2 _defaultBackground;


    Typewritter typewritter;
};