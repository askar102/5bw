#include "dialogPopup.h"

Font DialogPopup::_font;

// loading fucking russian words
void DialogPopup::Init()
{
    static int codepoints[512];
    int count = 0;

    for (int i = 32; i < 128; i++)
        codepoints[count++] = i;

    for (int i = 0x0400; i <= 0x04FF; i++)
        codepoints[count++] = i;

    _font = LoadFontEx("resources/fonts/arial.ttf", 30, codepoints, count);
}

void DialogPopup::Show(const std::string& text, const SpriteV2* anchor)
{
    _anchor = anchor;
    _queue = { text };
    _queueIndex = 0;
    _onFinish = nullptr;
    _visible = true;

    _tailTex = {LoadTexture("resources/popupTail.png"), {}};
    _tailSprite.SetResource(&_tailTex);
    _tailSprite.SetPosition({100, 300});

    StartLine(text);
}

void DialogPopup::ShowLines(const std::vector<std::string>& lines, const SpriteV2* anchor, std::function<void()> onFinish)
{
    if (lines.empty()) return;

    _anchor = anchor;
    _queue = lines;
    _queueIndex = 0;
    _onFinish = std::move(onFinish);
    _visible = true;

    _tailTex =  {LoadTexture("resources/popupTail.png"), {}};
    _tailSprite.SetResource(&_tailTex);
    _tailSprite.SetPosition({100, 300});

    StartLine(_queue[0]);
}

void DialogPopup::Skip()
{
    if (!_visible) return;

    if (_typing)
    {
        _displayed = _fullText;
        _typing = false;
        _pausing = false;
        return;
    }

    _queueIndex++;
    if (_queueIndex < _queue.size())
    {
        StartLine(_queue[_queueIndex]);
    }
    else
    {
        Hide();
        if (_onFinish)
            _onFinish();
    }
}

void DialogPopup::Hide()
{
    _visible = false;
    _typing = false;
    _pausing = false;
    
    _displayed.clear();
    _fullText.clear();
}

void DialogPopup::Update(float dt)
{
    if (!_visible) return;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER))
        Skip();

    // pause
    // if (_pausing)
    // {
    //     _pauseTimer -= dt;
    //     if (_pauseTimer <= 0.0f)
    //     {
    //         _pausing = false;
    //         _queueIndex++;
    //         if (_queueIndex < _queue.size())
    //             StartLine(_queue[_queueIndex]);
    //         else
    //         {
    //             Hide();
    //             if (_onFinish)
    //                 _onFinish();
    //         }
    //     }
    //     return;
    // }

    // Typewriter
    if (!_typing) return;

    _charTimer += dt;
    float interval = 1.0f / charsPerSecond;

    while (_charTimer >= interval && _displayed.size() < _fullText.size())
    {
        _charTimer -= interval;
        _displayed += _fullText[_displayed.size()];
    }

    if (_displayed.size() >= _fullText.size())
    {
        _typing = false;

        if (_queueIndex + 1 < _queue.size() && linePause > 0.0f)
        {
            _pausing = true;
            _pauseTimer = linePause;
        }
    }
}


void DialogPopup::Draw()
{
    if (!_visible || !_anchor) return;

    Vector2 pos = _anchor->GetPosition();
    Vector2 size = _anchor->GetSize();

    bool flipLeft = (pos.x > GetScreenWidth() * 0.5f);

    DrawBubble(pos, size, flipLeft);
    // printf("glyphs = %d\n", font.glyphCount);
}

void DialogPopup::StartLine(const std::string& text)
{
    _fullText = text;
    _displayed.clear();
    _charTimer = 0.0f;
    _typing = true;
    _pausing = false;
}

std::vector<std::string> DialogPopup::WrapText(const std::string& text) const
{
    std::vector<std::string> lines;
    if (text.empty()) return lines;

    float innerWidth = maxWidth - padding * 2.0f;

    std::string current;
    std::string word;

    auto pushWord = [&]() {
        if (word.empty()) return;
        std::string candidate = current.empty() ? word : (current + " " + word);
        // MeasureTextEx(font, line.c_str(), fontSize, 2).x
        if (MeasureTextEx(_font, candidate.c_str(), fontSize, 2).x <= static_cast<int>(innerWidth))
        {
            current = candidate;
        }
        else
        {
            if (!current.empty()) lines.push_back(current);
            current = word;
        }
        word.clear();
    };

    for (char c : text)
    {
        if (c == ' ' || c == '\n')
        {
            pushWord();
            if (c == '\n')
            {
                lines.push_back(current);
                current.clear();
            }
        }
        else
        {
            word += c;
        }
    }
    pushWord();
    if (!current.empty()) lines.push_back(current);

    return lines;
}

Vector2 DialogPopup::MeasureBubble(const std::vector<std::string>& lines) const
{
    float maxW = 0.0f;
    for (const auto& line : lines)
        maxW = std::max(maxW, static_cast<float>(MeasureText(line.c_str(), fontSize)));

    float w = maxW + padding * 2.0f;
    float h = static_cast<float>(lines.size()) * (fontSize + 4) + padding * 2.0f;

    return { w, h };
}

void DialogPopup::DrawBubble(Vector2 anchorPos, Vector2 anchorSize, bool flipLeft)
{
    auto wrappedFull = WrapText(_fullText);
    auto wrappedDisp = WrapText(_displayed);

    Vector2 bubbleSize = MeasureBubble(wrappedFull.empty() ? std::vector<std::string>{" "} : wrappedFull);

    float bubbleX, bubbleY;
    bubbleY = anchorPos.y - anchorSize.y * 0.5f + offsetY - bubbleSize.y;

    bubbleX = flipLeft ? anchorPos.x - bubbleSize.x + offsetX : anchorPos.x + offsetX;

    if (bubbleX < 4.0f)               bubbleX = 4.0f;
    if (bubbleX + bubbleSize.x > GetScreenWidth() - 4.0f)
    bubbleX = GetScreenWidth() - 4.0f - bubbleSize.x;

    Rectangle rect = { bubbleX, bubbleY, bubbleSize.x, bubbleSize.y };

    // bubble's konstruktivno ten'
    DrawRectangleRounded(
        { rect.x + 2, rect.y + 2, rect.width, rect.height },
        0.2f, 6,
        Fade(BLACK, 0.22f)
    );

    // bubble body
    DrawRectangleRounded(rect, 0.2f, 6, WHITE);
    DrawRectangleRoundedLines(rect, 0.2f, 6, Fade(BLACK, 0.4f));

    float tx = rect.x + padding;
    float ty = rect.y + padding;
    int lineH = fontSize + 4;

    for (const auto& line : wrappedDisp)
    {
        DrawTextEx(_font, line.c_str(), {tx, ty}, fontSize, 2, GRAY);
        // DrawTextEx(
        //     Game::GetResources().GetFont(),
        //     _label.c_str(),
        //     (Vector2){ textX, pos.y - (float)_textFontSize / 2},
        //     _textFontSize,
        //     2,
        //     _textColor
        // );
        ty += lineH;
    }

    if (!_typing && !_pausing)
    {
        const char* hint = (_queueIndex + 1 < _queue.size()) ? "PIZDA >" : "PIZDA";
        int hintSize = 10;
        float hx = rect.x + rect.width - MeasureText(hint, hintSize) - padding * 0.5f;
        float hy = rect.y + rect.height - hintSize - padding * 0.4f;
        DrawText(hint, static_cast<int>(hx), static_cast<int>(hy), hintSize, Fade(BLACK, 0.35f));
    }
}