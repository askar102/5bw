#pragma once
#include "../raylib/raylib.h"

class Sprite {
private:
    Vector2 _position{0, 0};
    Texture2D* _texture = nullptr;

    Vector2 _size;

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
     * @param texturePath New texture path
     */
    void setTexture(Texture2D* texture) 
    {
        this->_texture = texture;

        if (_texture) {
            _size = {(float)_texture->width, (float)_texture->height};
        }
    }

    /**
     * @brief Set the sprite size
     * 
     * @param w width
     * @param h height
     */
    void setSize(float w, float h) {
        _size = {w, h};
    }

    Vector2 getSize() const {
        return _size;
    }

    /**
     * @brief Get the sprite rect (hitbox)
     * 
     * @return Rectangle
     */ 
    Rectangle getRect() const {
        return {_position.x, _position.y, _size.x, _size.y};
    }

    /**
     * @brief Draw the texture
     *
     */
    virtual void Draw() 
    {
        if (!_texture) return;

        Rectangle src = {0, 0, (float)_texture->width, (float)_texture->height};
        Rectangle dest = {_position.x, _position.y, _size.x, _size.y};

        DrawTexturePro(*_texture, src, dest, {0, 0}, 0.0f, WHITE);
        // DrawTexture(_texture, _position.x, _position.y, WHITE);
    }
};