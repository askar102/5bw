#pragma once

#include <functional>
#include <string>
#include <vector>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"

class DialogPopup {
public:
    int fontSize = 15;
    float charsPerSecond = 50.0f;
    float linePause = 0.8f;
    float padding = 14.0f;
    float maxWidth = 250.0f;
    float tailSize = 10.0f;
    float offsetY = -10.0f;
    float offsetX = 0.0f;

    static void Init();

    void Show(const std::string& text, const SpriteV2* anchor);

    void ShowLines(const std::vector<std::string>& lines, const SpriteV2* anchor, std::function<void()> onFinish = nullptr);

    void Update(float dt);
    void Draw();

    void Hide();
    bool IsVisible() const 
    {
        return _visible; 
    }

    void Skip();

private:
    const SpriteV2* _anchor = nullptr;
    std::string  _fullText;
    std::string _displayed;
    float  _charTimer = 0.0f;
    float _pauseTimer = 0.0f;
    bool  _typing = false;
    bool  _pausing = false;
    bool  _visible = false;

    std::vector<std::string> _queue;
    size_t _queueIndex = 0;
    std::function<void()> _onFinish;

    void StartLine(const std::string& text);
    void DrawBubble(Vector2 anchorPos, Vector2 anchorSize, bool flipLeft);

    std::vector<std::string> WrapText(const std::string& text) const;

    Vector2 MeasureBubble(const std::vector<std::string>& lines) const;


    SpriteV2 _tailSprite; 
    TextureResource _tailTex;

    static Font _font;
};