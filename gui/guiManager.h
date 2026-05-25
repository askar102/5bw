/**
 * @file guiManager.h
 * @author askar102
 * @brief GUI container — holds and ticks all GUI elements for a state
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #pragma once

 #include <memory>
 #include <vector>
 
 #include "gui.h"
 
 class GuiManager {
 public:
     Gui* Add(std::unique_ptr<Gui> element);
     void Clear();
 
     void Update();
     void Draw() const;
 
 private:
     std::vector<std::unique_ptr<Gui>> _elements;
 };