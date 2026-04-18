#pragma once
#include "../raylib/raylib.h"

class NakedSprite {
private:
    Vector2 _position{0, 0};
    Texture2D* _texture = nullptr;

    bool _loaded = false;

public:
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
     * @param texture New texture object
     */
    void setTexture(Texture2D* texture) 
    {
        this->_texture = texture;
    }

    /**
     * @brief Draw the texture
     *
     */
    virtual void Draw() 
    {
        if (_texture)
            DrawTexture(*_texture, _position.x, _position.y, WHITE);
    }
};