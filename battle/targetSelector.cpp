/**
 * @file targetSelector.cpp
 * @author askar102
 * @brief Target selection system
 * @date 2026-05-30
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "targetSelector.h"
 #include "../misc/inputBridge.h"

 void TargetSelector::Arm(BattleEntity* caster,
                          std::vector<BattleEntity*> targets,
                          TargetAbilityDesc desc)
 {
     // отменяем если было
     if (_active)
         Cancel();
 
     _caster  = caster;
     _targets = std::move(targets);
     _desc    = std::move(desc);
     _active  = true;
 
     // запрещаем выбор
     for (BattleEntity* t : _targets)
     {
         if (t)
             t->canSelected = false;
     }
 }
 
 void TargetSelector::Cancel()
 {
     if (!_active) return;
 
     RestoreTargets();
     _active = false;
 
     if (_desc.onCancel)
         _desc.onCancel();
 
     _caster  = nullptr;
     _targets.clear();
 }
 
 bool TargetSelector::HandleInput(Vector2 mouse)
 {
     if (!_active) return false;
 
     //отмена
     if (InputBridge::KeyPressed(KEY_ESCAPE) || InputBridge::MouseButtonPressed(MOUSE_RIGHT_BUTTON))
     {
         Cancel();
         return true;
     }
 
     // потдверждение
     if (InputBridge::MouseButtonPressed(MOUSE_LEFT_BUTTON))
     {
         BattleEntity* hovered = FindHovered(mouse);
 
         if (hovered && _desc.onConfirm && _caster)
         {
             RestoreTargets();
             _active = false;
 
             _desc.onConfirm(*_caster, *hovered);
 
             _caster  = nullptr;
             _targets.clear();
         }
         // если не попали ни в кого ничего не делаем
         return hovered != nullptr;
     }
 
     return false;
 }
 
 void TargetSelector::Draw(Vector2 mouse) const
 {
     if (!_active) return;
 
     // cusror
     DrawCircleLines(
         static_cast<int>(mouse.x),
         static_cast<int>(mouse.y),
         CURSOR_RADIUS,
         CURSOR_COLOR
     );
     // center
     DrawCircleV(mouse, 2.0f, CURSOR_COLOR);
 
     // outline
     BattleEntity* hovered = FindHovered(mouse);
     if (!hovered) return;
 
     Rectangle r = hovered->getSprite().GetWorldRect();
     float pad   = OUTLINE_PADDING;
 
     DrawRectangleLinesEx(
         { r.x - pad, r.y - pad, r.width + pad * 2.0f, r.height + pad * 2.0f },
         2.0f,
         OUTLINE_COLOR
     );
 
     // hint
     const char* hint = "Click to target";
     int fontSize = 12;
     int textW    = MeasureText(hint, fontSize);
     DrawText(
         hint,
         static_cast<int>(r.x + r.width * 0.5f - textW * 0.5f),
         static_cast<int>(r.y - pad - fontSize - 4),
         fontSize,
         OUTLINE_COLOR
     );
 }
 

 void TargetSelector::RestoreTargets()
 {
     for (BattleEntity* t : _targets)
     {
         if (t)
             t->canSelected = true;
     }
 }
 
 BattleEntity* TargetSelector::FindHovered(Vector2 mouse) const
 {
     for (BattleEntity* t : _targets)
     {
         if (!t || !t->Alive()) continue;
 
         if (CheckCollisionPointRec(mouse, t->getSprite().GetWorldRect()))
             return t;
     }
     return nullptr;
 }