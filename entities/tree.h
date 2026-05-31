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
 
 #include "uniqueHitbox.h"
 #include "../core/resourceManager.h"
  
 class Tree : public UniqueHitbox {
 public:
    // hitboxOffset - смещение хитбокса от центра
     Tree(TextureResource* treeResource,
          Vector2 visualSize   = {100.0f, 100.0f},
          Vector2 hitboxSize   = {40.0f,  30.0f},
          Vector2 hitboxOffset = {0.0f,   0.0f});
  
 };
  
 