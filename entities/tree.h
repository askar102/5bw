/**
 * @file tree.h
 * @author askar102
 * @brief Tree map entity — visual crown + tight trunk hitbox
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #pragma once
 
 #include "mapEntity.h"
 #include "../core/resourceManager.h"
  
 class Tree : public MapEntity {
 public:
     // visualSize  — размер визуального спрайта (крона + ствол целиком)
     // hitboxSize  — размер хитбокса (обычно только ствол, меньше и ниже)
     // hitboxOffset — смещение хитбокса от центра позиции
     Tree(TextureResource* treeResource,
          Vector2 visualSize   = {100.0f, 100.0f},
          Vector2 hitboxSize   = {40.0f,  30.0f},
          Vector2 hitboxOffset = {0.0f,   0.0f});
  
     // Tree не нужен отдельный Update, но оставим возможность переопределить
 };
  
 