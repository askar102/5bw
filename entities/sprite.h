#pragma once
#include "../raylib/raylib.h"

class Sprite {
private:
    Vector2 _position{0, 0};
    Texture2D _texture{0};

    bool _loaded = false;

public:
    /**
     * @brief Destroy the Sprite object
     * 
     */
    ~Sprite() 
    {
        UnloadTexture(_texture);
    }

    /**
     * @brief Get the Positon object
     * 
     * @return Vector2 
     */
    Vector2 getPosition() const 
    {
        return _position;
    }

    /**
     * @brief Set the Position object
     * 
     * @param position New sprite position
     */
    void setPosition(Vector2 newPosition)
    {
        this->_position = newPosition;
    }

    /**
     * @brief Set the Texture object
     * 
     * @param texturePath New texture path
     */
    void setTexture(const char* texturePath) 
    {
        if (_loaded) 
        {
            TraceLog(LOG_WARNING, "Sprite: texture already loaded, replacing it");
            UnloadTexture(_texture);
        }

        this->_texture = LoadTexture(texturePath);
        _loaded = true;
    }

    /**
     * @brief Draw the texture
     *
     */
    virtual void Draw() 
    {
        DrawTexture(_texture, _position.x, _position.y, WHITE);
    }
};