/**
 * @file resourceManager.h
 * @author askar102
 * @brief Manager for loading and unloading all textures
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #include "resourceManager.h"

 ResourceManager::ResourceManager() 
 {
 }
 
 ResourceManager::~ResourceManager() 
 {
     Unload();
 }
 
 void ResourceManager::Load()
 {
     if (!_textures.empty())
     {
         return;
     }
 
     _textures[TextureID::BattleBg] = 
     {
         LoadTexture("resources/battleBG.png"),
         {}
     };
 
     _textures[TextureID::Player] = 
     {
         LoadTexture("resources/player.png"),
         {}
     };
 
     _textures[TextureID::Tree] = 
     {
         LoadTexture("resources/tree.png"),
         {}
     };
     
     _textures[TextureID::Enemy] = 
     {
         LoadTexture("resources/enemy.png"),
         {}
     };
 
     _textures[TextureID::AbilityIcon] =
     {
         LoadTexture("resources/option.png"),
         {}
     };
 
     // CardGuy's textures
     _textures[TextureID::CardVFX] =
     {
         LoadTexture("resources/card.png"),
         {}
     };
 
     _textures[TextureID::CardAttack] = 
     {
         LoadTexture("resources/cardAttack.png"),
         {}
     };
 
     _textures[TextureID::CardGuyAtlas] =
     {
         LoadTexture("resources/cardGuy.png"),
         MakeGrid(88, 128, 3)
     };
 
     for (auto& [id, res] : _textures)
     {
         if (res.texture.id == 0)
         {
            res.texture = LoadTexture("resources/textureError.png");
            TraceLog(LOG_WARNING, "[resourceManager] Cannot find texture");
         }
     }
 }
 
 void ResourceManager::Unload()
 {
     for (auto& [id, res] : _textures)
     {
         if (res.texture.id != 0)
             UnloadTexture(res.texture);
     }
     _textures.clear();
 }
 
 
 TextureResource& ResourceManager::Get(TextureID id)
 {
     return _textures.at(id);
 }
 
 std::vector<Rectangle> ResourceManager::MakeGrid(int w, int h, int cols)
 {
     std::vector<Rectangle> frames;
 
     for (int i = 0; i < cols; i++) {
         frames.push_back({(float)i * w, 0.0f, (float)w, (float)h});
     }
 
     return frames;
 }
 