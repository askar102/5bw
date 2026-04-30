#pragma once
#include "../raylib/raylib.h"

class Sprite {
private:
    struct Costume {
        bool enabled = false;
        int index = 0;
        int width = 88;
        int height = 128;
        int total = 3;
    };

    Vector2 _position{0, 0};
    Texture2D* _texture = nullptr;
    float _rotation = 0.0f;

    Vector2 _size;

    bool _isSolid = false;
    static bool _drawHitboxes;
    bool _canDrawHitboxes = true;

    Rectangle _rect = {_position.x, _position.y, _size.x, _size.y};
    Costume _costume;
    bool _hasTimedCostume = false;
    bool _previousCostumeEnabled = false;
    int _previousCostumeIndex = 0;
    double _costumeRevertAt = 0.0;

    bool _isMirror = false;
    bool _hasTimedMirror = false;
    bool _previousMirrorState = false;
    double _mirrorRevertAt = 0.0;

    float _alpha = 1.0f;

    void UpdateRect()
    {
        _rect.x = _position.x;
        _rect.y = _position.y;
    }

    void ApplyCostumeState(bool enabled, int costumeIndex)
    {
        if (!_texture) {
            return;
        }

        if (enabled && _costume.total > 0) {
            if (costumeIndex < 0) {
                costumeIndex = 0;
            }
            if (costumeIndex >= _costume.total) {
                costumeIndex = _costume.total - 1;
            }

            _costume.enabled = true;
            _costume.index = costumeIndex;
            _size = {(float)_costume.width, (float)_costume.height};
        } else {
            _costume.enabled = false;
            _costume.index = 0;
            _size = {(float)_texture->width, (float)_texture->height};
        }

        _rect.width = _size.x;
        _rect.height = _size.y;
        UpdateRect();
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
        if (_texture == texture) {
            return;
        }

        this->_texture = texture;
        _costume.enabled = false;
        _costume.index = 0;
        _hasTimedCostume = false;
        _previousCostumeEnabled = false;
        _previousCostumeIndex = 0;
        _costumeRevertAt = 0.0;
        _isMirror = false;
        _hasTimedMirror = false;
        _previousMirrorState = false;
        _mirrorRevertAt = 0.0;

        if (_texture) {
            _size = {(float)_texture->width, (float)_texture->height};
            _rect.width = _size.x;
            _rect.height = _size.y;
            UpdateRect();
        }
    }

    /**
     * @brief ставим костюм из аталаса
     * 
     * @param costumeIndex 
     */
    void setCostume(int costumeIndex)
    {
        if (!_texture) {
            return;
        }

        _hasTimedCostume = false;
        ApplyCostumeState(true, costumeIndex);
    }

    /**
     * @brief здесь перегрузка: мы типо можем поставить лайфтайм
     * 
     * @param costumeIndex 
     * @param lifetime вот и он
     */
    void setCostume(int costumeIndex, float lifetime)
    {
        if (!_texture) {
            return;
        }

        if (lifetime <= 0.0f) {
            setCostume(costumeIndex);
            return;
        }

        // If a timed costume is already active, keep its original revert target.
        // This allows repeated casts of the same skill to extend duration
        // without "locking" into the current costume forever.
        const bool shouldCapturePrevious =
            !_hasTimedCostume || GetTime() >= _costumeRevertAt;
        if (shouldCapturePrevious) {
            _previousCostumeEnabled = _costume.enabled;
            _previousCostumeIndex = _costume.index;
            
            const bool looksLikeCostumeAtlas =
                _texture->width == (_costume.width * _costume.total) &&
                _texture->height == _costume.height;
            if (!_previousCostumeEnabled && looksLikeCostumeAtlas) {
                _previousCostumeEnabled = true;
                _previousCostumeIndex = 0;
            }
        }
        ApplyCostumeState(true, costumeIndex);

        _hasTimedCostume = true;
        _costumeRevertAt = GetTime() + lifetime;
    }

    void disableCostume()
    {
        if (!_texture) {
            return;
        }

        _hasTimedCostume = false;
        ApplyCostumeState(false, 0);
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

    void setMirror(bool isMirror)
    {
        _hasTimedMirror = false;
        _isMirror = isMirror;
    }

    void setMirror(bool isMirror, float lifetime)
    {
        if (lifetime <= 0.0f) {
            setMirror(isMirror);
            return;
        }

        if (!_hasTimedMirror || GetTime() >= _mirrorRevertAt) {
            _previousMirrorState = _isMirror;
        }

        _isMirror = isMirror;
        _hasTimedMirror = true;
        _mirrorRevertAt = GetTime() + lifetime;
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
        /**
         * TODO: generated by ai, refactor and fix later:
         * 
         * - costume system
         * - mirror system
         */
        if (!_texture) return;
        if (_hasTimedCostume && GetTime() >= _costumeRevertAt) {
            ApplyCostumeState(_previousCostumeEnabled, _previousCostumeIndex);
            _hasTimedCostume = false;
        }
        if (_hasTimedMirror && GetTime() >= _mirrorRevertAt) {
            _isMirror = _previousMirrorState;
            _hasTimedMirror = false;
        }

        Rectangle src = {0, 0, (float)_texture->width, (float)_texture->height};
        if (_costume.enabled) {
            src.x = (float)(_costume.index * _costume.width);
            src.y = 0;
            src.width = (float)_costume.width;
            src.height = (float)_costume.height;
        }
        if (_isMirror) {
            src.x += src.width;
            src.width *= -1.0f;
        }
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
