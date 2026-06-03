#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

#include "../misc/configReader.h"

class DialogPopUp {
public:
    DialogPopUp() = default;
    DialogPopUp(const SpriteV2* entity);

    void Show(uint32_t dialogID);
    void Next();

    void Draw();
    void Draw(const SpriteV2* entity);

    void Update(float dt);

private:
    static std::vector<std::string> _text;
    bool _visible = false;
    
    const SpriteV2* _anchor;
    Rectangle _rect;
};