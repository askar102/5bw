#include "dialog.h"
#include "typewritter.h"

#include "../misc/inputBridge.h"

#include <cmath>

namespace {
    constexpr float BOX_W = 560.0f;
    constexpr float BOX_H = 110.0f;
    constexpr float BOX_MARGIN_BOTTOM = 20.0f;
    constexpr float PADDING = 14.0f;
    constexpr float PORTRAIT_SIZE = 72.0f;
    constexpr int TEXT_SIZE = 18;
    constexpr float CHOICE_LINE_H = 24.0f;
}

TextureResource Dialog::_storyTexture;
SpriteV2 Dialog::_storyBackground;
Font Dialog::_font;

void Dialog::Init()
{
    _storyTexture = {LoadTexture("resources/dialog_story.png"), {}};

    _storyBackground.SetResource(&_storyTexture);
    _storyBackground.SetPosition({640/2.0f, 480/2.0f});
    _storyBackground.SetAlpha(0.6f);

    // same cyrillic-range trick as DialogPopup::Init - Text and ResourceManager
    // fonts are ascii-only, so anything drawing russian text needs its own font here
    static int codepoints[512];
    int count = 0;

    for (int i = 32; i < 128; i++)
        codepoints[count++] = i;

    for (int i = 0x0400; i <= 0x04FF; i++)
        codepoints[count++] = i;

    _font = LoadFontEx("resources/fonts/arial.ttf", 30, codepoints, count);
}

void Dialog::Show(std::string text, DialogMode mode, std::function<void()> onClose, Color textColor)
{
    ShowInternal({std::move(text)}, mode, nullptr, {}, textColor, std::move(onClose));
}

void Dialog::Show(std::vector<std::string> lines, DialogMode mode, std::function<void()> onClose, Color textColor)
{
    ShowInternal(std::move(lines), mode, nullptr, {}, textColor, std::move(onClose));
}

void Dialog::ShowWithPortrait(std::vector<std::string> lines, DialogMode mode, TextureResource* portrait, std::function<void()> onClose, Color textColor)
{
    ShowInternal(std::move(lines), mode, portrait, {}, textColor, std::move(onClose));
}

void Dialog::ShowChoice(std::vector<std::string> lines, DialogMode mode, std::vector<DialogChoice> choices, TextureResource* portrait, Color textColor)
{
    ShowInternal(std::move(lines), mode, portrait, std::move(choices), textColor, nullptr);
}

void Dialog::ShowInternal(std::vector<std::string> lines, DialogMode mode, TextureResource* portrait, std::vector<DialogChoice> choices, Color textColor, std::function<void()> onClose)
{
    _mode = mode;
    _portrait = portrait;
    _choices = std::move(choices);
    _selectedChoice = 0;
    _showingChoices = false;
    _onClose = std::move(onClose);
    _visible = true;

    Vector2 pos;
    float maxWidth;

    switch (mode)
    {
        case DialogMode::Mind:
        case DialogMode::Npc:
        {
            Rectangle box = GetBoxRect();
            float textX = box.x + PADDING + (_portrait ? PORTRAIT_SIZE + PADDING : 0.0f);
            pos = { textX, box.y + PADDING };
            maxWidth = box.x + box.width - PADDING - textX;
            break;
        }
        case DialogMode::StoryCenter:
            pos = { 640.0f/2.0f - 220.0f, 480.0f/2.0f - 20.0f };
            maxWidth = 440.0f;
            break;
        case DialogMode::StoryDown:
        default:
            pos = { 640.0f/2.0f - 220.0f, 480.0f - 110.0f };
            maxWidth = 440.0f;
            break;
    }

    _typewritter.SetFont(&_font);
    _typewritter.SetMaxWidth(maxWidth);
    _typewritter.SetFontSize(TEXT_SIZE);
    _typewritter.SetColor(textColor);

    _typewritter.SpawnAt(std::move(lines), pos, 40.0f, true);
    _typewritter.InOver([this] () {
        if (!_choices.empty())
        {
            _showingChoices = true;
            return;
        }

        _visible = false;

        auto onClose = _onClose;
        if (onClose) onClose();
    });
}

void Dialog::Update(float dt)
{
    if (!_visible) return;

    if (_mode == DialogMode::StoryCenter || _mode == DialogMode::StoryDown) _storyBackground.Update(dt);

    if (_showingChoices)
    {
        if (_choices.empty()) return;

        if (InputBridge::KeyPressed(KEY_DOWN))
            _selectedChoice = (_selectedChoice + 1) % static_cast<int32_t>(_choices.size());

        if (InputBridge::KeyPressed(KEY_UP))
            _selectedChoice = (_selectedChoice - 1 + static_cast<int32_t>(_choices.size())) % static_cast<int32_t>(_choices.size());

        if (InputBridge::KeyPressed(KEY_ENTER))
            SelectAnswer(_selectedChoice);

        return;
    }

    _typewritter.Update(dt);
}

void Dialog::Draw()
{
    if (!_visible) return;

    if (_mode == DialogMode::StoryCenter || _mode == DialogMode::StoryDown) _storyBackground.Draw();
    if (_mode == DialogMode::Mind || _mode == DialogMode::Npc) DrawBox();

    _typewritter.Draw();

    if (_showingChoices)
        DrawChoices();
    else if (_typewritter.IsFullyShown())
        DrawContinueHint();
}

// private

Rectangle Dialog::GetBoxRect() const
{
    return { (640.0f - BOX_W) / 2.0f, 480.0f - BOX_H - BOX_MARGIN_BOTTOM, BOX_W, BOX_H };
}

void Dialog::DrawBox()
{
    Rectangle box = GetBoxRect();

    DrawRectangleRounded({box.x + 3, box.y + 3, box.width, box.height}, 0.12f, 8, Fade(BLACK, 0.35f));
    DrawRectangleRounded(box, 0.12f, 8, Fade(BLACK, 0.75f));
    DrawRectangleRoundedLines(box, 0.12f, 8, Fade(WHITE, 0.8f));

    if (!_portrait) return;

    Rectangle portraitRect = { box.x + PADDING, box.y + PADDING, PORTRAIT_SIZE, PORTRAIT_SIZE };

    Rectangle portraitSrc = _portrait->frames.empty()
        ? Rectangle{0, 0, (float)_portrait->texture.width, (float)_portrait->texture.height}
        : _portrait->frames[0];

    DrawRectangleRec(portraitRect, BLACK);
    DrawTexturePro(_portrait->texture, portraitSrc, portraitRect, {0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(portraitRect, 2.0f, WHITE);
}

void Dialog::DrawChoices()
{
    float startY;

    switch (_mode)
    {
        case DialogMode::Mind:
        case DialogMode::Npc:
        {
            // rendered bottom-aligned inside the box itself - a fixed offset
            // below the box would run past the bottom of the 480px screen
            Rectangle box = GetBoxRect();
            float choicesHeight = static_cast<float>(_choices.size()) * CHOICE_LINE_H;
            startY = box.y + box.height - PADDING - choicesHeight;
            break;
        }
        case DialogMode::StoryCenter:
            startY = 480.0f/2.0f + 40.0f;
            break;
        case DialogMode::StoryDown:
        default:
            startY = 480.0f - 50.0f;
            break;
    }

    for (int32_t i = 0; i < static_cast<int32_t>(_choices.size()); ++i)
    {
        const std::string& text = _choices[i].text;
        float textW = MeasureTextEx(_font, text.c_str(), TEXT_SIZE, 2.0f).x;

        float x = 640.0f/2.0f - textW/2.0f;
        float y = startY + i * CHOICE_LINE_H;

        bool selected = (i == _selectedChoice);
        Color color = selected ? YELLOW : WHITE;

        DrawTextEx(_font, text.c_str(), {x, y}, TEXT_SIZE, 2.0f, color);

        if (selected)
        {
            float cx = x - 14.0f;
            float cy = y + TEXT_SIZE * 0.5f;

            DrawTriangle({cx, cy - 6}, {cx, cy + 6}, {cx + 8, cy}, YELLOW);
        }
    }
}

void Dialog::DrawContinueHint()
{
    if (fmodf((float)GetTime(), 0.8f) > 0.4f) return;

    Vector2 pos;

    switch (_mode)
    {
        case DialogMode::Mind:
        case DialogMode::Npc:
        {
            Rectangle box = GetBoxRect();
            pos = { box.x + box.width - 24.0f, box.y + box.height - 22.0f };
            break;
        }
        case DialogMode::StoryCenter:
            pos = { 640.0f/2.0f, 480.0f/2.0f + 40.0f };
            break;
        case DialogMode::StoryDown:
        default:
            pos = { 640.0f/2.0f, 480.0f - 60.0f };
            break;
    }

    DrawTriangle({pos.x - 6, pos.y}, {pos.x + 6, pos.y}, {pos.x, pos.y + 8}, WHITE);
}

void Dialog::SelectAnswer(int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(_choices.size())) return;

    auto onSelect = _choices[index].onSelect;
    auto onClose = _onClose;

    _visible = false;
    _showingChoices = false;
    _choices.clear();

    if (onSelect) onSelect();
    if (onClose) onClose();
}
