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
    TraceLog(LOG_INFO, "[resourceManager] loading textures...");

     if (!_textures.empty())
     {
         return;
     }
     
     _textures[TextureID::ErrorTexture] =
     {
        LoadTexture("resources/textureError.png"),
        {}
     };

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
 
     _textures[TextureID::CardGuy] =
     {
         LoadTexture("resources/cardGuy.png"),
         MakeGrid(88, 128, 3)
     };

     _textures[TextureID::MenuBackground] =
     {
         LoadTexture("resources/menuBackground.png"),
         {}
     };

     _textures[TextureID::GuiButton] =
     {
         LoadTexture("resources/button.png"),
         {}
     };

     _textures[TextureID::GuiNewGameButton] =
     {
         LoadTexture("resources/newGameButton.png"),
         {}
     };

     _textures[TextureID::GuiContinueButton] =
     {
         LoadTexture("resources/continueButton.png"),
         {}
     };

     _textures[TextureID::GuiTradesButton] =
     {
         LoadTexture("resources/tradesButton.png"),
         {}
     };

 
     for (auto& [id, res] : _textures)
     {
         if (res.texture.id == 0)
         {
            res.texture = Get(TextureID::ErrorTexture).texture;
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

     for (auto& [id, res] : _customTextures)
     {
         if (res.texture.id != 0)
             UnloadTexture(res.texture);
     }

     _customTextures.clear();

 }
 
 
 TextureResource& ResourceManager::Get(TextureID id)
 {
     return _textures.at(id);
 }

 TextureResource& ResourceManager::Get(std::string name)
 {
    if (_customTextures.find(name) != _customTextures.end())
        return _customTextures[name];
    
    TraceLog(LOG_INFO, "[resourceManager] Loading custom texture %s...", name.c_str());

    Texture2D tex = LoadTexture(("resources/" + name + ".png").c_str());

    if (tex.id == 0)
    {
        TraceLog(LOG_WARNING, "[resourceManager] Cannot find texture name: %s", name.c_str());
        tex = Get(TextureID::ErrorTexture).texture;
    }

    _customTextures[name] = {
        tex,
        MakeGrid(88, 128, 3)
    };

    return _customTextures[name];
 }
 
 std::vector<Rectangle> ResourceManager::MakeGrid(int w, int h, int cols)
 {
     std::vector<Rectangle> frames;
 
     for (int i = 0; i < cols; i++) {
         frames.push_back({(float)i * w, 0.0f, (float)w, (float)h});
     }
 
     return frames;
 }