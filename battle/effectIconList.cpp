/**
 * @file effectIconList.cpp
 * @author askar102
 * @brief Container for multiple effect icons displayed in a row above a unit
 * @date 2026-05-28
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "effectIconList.h"
 #include "../core/game.h"
 
 void EffectIconList::Show(const std::string& textureName, float duration)
 {
     // Если иконка с таким именем уже есть — обновляем таймер, не дублируем
     for (auto& entry : _icons)
     {
         if (entry.textureName == textureName)
         {
             entry.remainingDuration = duration;
             entry.icon.Show(textureName, duration);
             return;
         }
     }
 
     Entry entry;
     entry.textureName       = textureName;
     entry.remainingDuration = duration;
     entry.icon.Show(textureName, duration);
 
     _icons.push_back(std::move(entry));
 }
 
 void EffectIconList::Update(float dt)
 {
     for (auto& entry : _icons)
         entry.icon.Update(dt);
 
     // Удаляем иконки, у которых таймер вышел
     _icons.erase(
         std::remove_if(_icons.begin(), _icons.end(),
             [](const Entry& e) { return !e.icon.IsVisible(); }),
         _icons.end()
     );
 }
 
 void EffectIconList::Draw(SpriteV2& unit)
 {
     if (_icons.empty()) return;
 
     Rectangle unitRect = unit.GetWorldRect();
 


     for (auto& entry : _icons)
     {
        entry.icon.Draw(unit);
     }
 }