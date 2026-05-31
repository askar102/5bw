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
    // visual
     _visual.SetResource(treeResource);
     _visual.SetSize(visualSize);

     _visual.SetCollide(false);
     _visual.SetCanDrawHiboxes(false);

     // hitbox
     _hitbox.SetResource(nullptr);
     _hitbox.SetRectSize(hitboxSize);
     _hitbox.SetCollide(true);

     // debug
     _hitbox.SetCanDrawHiboxes(true);
  
     _hitboxOffset = hitboxOffset;
 }
 