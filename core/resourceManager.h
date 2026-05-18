/**
 * @file resourceManager.h
 * @author askar102
 * @brief Manager for loading and unloading all textures
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #pragma once

 #include <vector>
 #include <unordered_map>
 #include <string>
 
 #include "../raylib/raylib.h"
 
 enum class TextureID {
     BattleBg,
     Player,
     Tree,
     Enemy,
     AbilityIcon,
     CardVFX,
     CardAttack,
     CardGuy,

     ErrorTexture
 };
 
 struct TextureResource {
     Texture2D texture;
     std::vector<Rectangle> frames;
 };
 
 class ResourceManager {
 private:
     std::unordered_map<TextureID, TextureResource> _textures;
     
     std::unordered_map<std::string, TextureResource> _customTextures;
 
     std::vector<Rectangle> MakeGrid(int w, int h, int cols);
 public:
     ResourceManager();
     ~ResourceManager();
 
     void Load();
 
     TextureResource& Get(TextureID id);
     TextureResource& Get(std::string name);

     void Unload();
 };
 