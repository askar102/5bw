/**
 * @file effectIconList.h
 * @author askar102
 * @brief Container for multiple effect icons displayed in a row above a unit
 * @date 2026-05-28
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #pragma once

 #include <vector>
 #include <string>
 
 #include "effectIcon.h"
 #include "../entities/spriteV2.h"
 
 class EffectIconList {
 public:
     // Добавляет новую иконку эффекта, не заменяя существующие
     void Show(const std::string& textureName, float duration);
 
     void Update(float dt);
 
     // unit — спрайт персонажа, иконки рисуются в ряд над ним
     void Draw(SpriteV2& unit);
 
     bool HasAny() const { return !_icons.empty(); }
     void Clear()        { _icons.clear(); }
 
 private:
     struct Entry {
         EffectIcon icon;
         std::string textureName; // храним чтобы не дублировать одинаковые
         float remainingDuration;
     };
 
     std::vector<Entry> _icons;
 
     static constexpr float ICON_SIZE    = 28.0f; // размер одной иконки
     static constexpr float ICON_SPACING = 4.0f;  // зазор между иконками
     static constexpr float ICON_OFFSET_Y = 50.0f; // сколько пикселей выше позиции юнита
 };