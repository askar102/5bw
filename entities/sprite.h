#pragma once
#include "../raylib/raylib.h"

class Sprite {
private:
    Vector2 _position{0, 0};
    Texture2D* _texture = nullptr;
    float _rotation = 0.0f;

    Vector2 _size;

    bool _isSolid = false;
    static bool _drawHitboxes;
    bool _canDrawHitboxes = true;

    Rectangle _rect = {_position.x, _position.y, _size.x, _size.y};

    float _alpha = 1.0f;

    void UpdateRect()
    {
        _rect.x = _position.x;
        _rect.y = _position.y;
    }

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
        UpdateRect();
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
            _rect.width = _size.x;
            _rect.height = _size.y;
            UpdateRect();
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
        UpdateRect();
    }

    void setRotation(float rotation)
    {
        _rotation = rotation;
    }

    float getRotation() const
    {
        return _rotation;
    }

    Vector2 getSize() const {
        return _size;
    }

    /**
     * @brief Get the sprite rect (hitbox)
     * 
     * @return Rectangle
     */ 
    Rectangle getRect() const 
    {
        return _rect;
    }

    /**
     * @brief  change size of the hitbox
     * 
     */
    void changeSizeOfRect(Vector2 size) 
    {
        _rect.width = size.x;
        _rect.height = size.y;
        UpdateRect();
    }

    /**
     * @brief The object has a collision or not
     * 
     * @param isSolid boolean
     */
    void setSolid(bool isSolid)
    {
        _isSolid = isSolid; 
    }
    
    /**
     * @brief Determine the object has a collision or not
     * 
     * @return true 
     * @return false 
     */
    bool getSolid() const
    {
        return _isSolid; 
    }

    /**
     * @brief Set the _DrawHitboxes bool object
     * 
     * @param value do u wanna draw hitboxes?
     */
    static void SetDrawHitboxes(bool value)
    {
        _drawHitboxes = value;
    }

    /**
     * @brief Get the _DrawHitboxes bool object
     * 
     * @return true 
     * @return false 
     */
    static bool GetDrawHitboxes()
    {
        return _drawHitboxes;
    }

    /**
     * @brief Does the static object _drawHiboxes depend on this sprite?
     * 
     * @param val 
     */
    void SetCanDrawHiboxes(bool val)
    {
        _canDrawHitboxes = val;
    }

    /**
     * @brief Set the Alpha of object
     * 
     * @param alpha 
     */
    void SetAlpha(float alpha)
    {
        _alpha = alpha;
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
        Vector2 origin = {0, 0};

        DrawTexturePro(*_texture, src, dest, origin, _rotation, Fade(WHITE, _alpha));

        if (_drawHitboxes) 
        {
            if (_canDrawHitboxes)
            {
                DrawRectanglePro(_rect, origin, _rotation, Fade(WHITE, 0.5f));
            }
        }
        
    }
};
