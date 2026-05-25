/**
 * @file guiManager.cpp
 * @author askar102
 * @brief GUI container — holds and ticks all GUI elements for a state
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "guiManager.h"
 
 Gui* GuiManager::Add(std::unique_ptr<Gui> element)
 {
     if (!element)
         return nullptr;
 
     Gui* raw = element.get();
     _elements.push_back(std::move(element));
     return raw;
 }
 
 void GuiManager::Clear()
 {
     _elements.clear();
 }
 
 void GuiManager::Update()
 {
     for (auto& el : _elements)
         el->Update();
 }
 
 void GuiManager::Draw() const
 {
     for (const auto& el : _elements)
         el->Draw();
 }