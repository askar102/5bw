/**
 * @file tree.cpp
 * @author askar102
 * @brief Tree map entity — visual crown + tight trunk hitbox
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #include "tree.h"
 
 Tree::Tree(TextureResource* treeResource,
            Vector2 visualSize,
            Vector2 hitboxSize,
            Vector2 hitboxOffset)
 {
     // --- Визуальный спрайт ---
     _visual.SetResource(treeResource);
     _visual.SetSize(visualSize);
     // Визуал никогда не участвует в коллизиях и не рисует свой хитбокс
     _visual.SetCollide(false);
     _visual.SetCanDrawHiboxes(false);
  
     // --- Хитбокс-спрайт ---
     // Ресурс не нужен — он только для коллизий и дебаг-отображения
     _hitbox.SetResource(nullptr);
     _hitbox.SetRectSize(hitboxSize);
     _hitbox.SetCollide(true);
     // Хитбокс рисует себя только в debug-режиме (SpriteV2::_drawHitboxes)
     _hitbox.SetCanDrawHiboxes(true);
  
     _hitboxOffset = hitboxOffset;
 }
 