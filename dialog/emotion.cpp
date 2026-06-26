#include "emotion.h"
#include "../core/game.h"

void Emotion::Init(const SpriteV2* anchor)
{
    _anchor = anchor;

    TextureResource& tex = Game::GetResources().Get(TextureID::Emotion);

    _popup.SetResource(&tex);
    // _popup.SetSize(POPUP_SIZE);
    _popup.SetCanDrawHiboxes(false);

    _emotion.SetResource(&tex);
    // _emotion.SetSize(ICON_SIZE);
    _emotion.SetCanDrawHiboxes(false);
}

void Emotion::Show(EmotionType type, PopupSize size, float duration)
{
    _popup.SetAnimation({0, 1}, 0.15f, false);
    // _emotion.SetFrame(static_cast<size_t>(type));
    _emotion.SetAnimation({2, 3, 4}, 0.15f, false);

    _animationDuration = duration;
    _animationTimer = 0.0f;
    _visible = true;

    _popup.SetAlpha(1.0f);
    _emotion.SetAlpha(1.0f);
}

void Emotion::Hide()
{
    _emotion.FadeOut(1.0f, [this] () {
        _emotion.SetAlpha(0.0f);
    });

    _popup.FadeOut(1.0f, [this] () {
        _popup.SetAlpha(0.0f);
        _visible = false;
    });

    _animationTimer = 0.0f;
}

void Emotion::Update(float dt)
{
    _popup.Update(dt);
    _emotion.Update(dt);

    if (!_visible) return;

    _animationTimer += dt;

    if (_animationTimer >= _animationDuration)
    {
        Hide();
        return;
    }

    // _popup.SetAlpha(0.0f);
    // _emotion.SetAlpha(0.0f);

    if (!_anchor) return;

    Vector2 anchorPos = _anchor->GetPosition();

    Vector2 pos = {_anchor->GetPosition().x, _anchor->GetPosition().y - 40.0f};

    _popup.SetPosition(pos);
    _emotion.SetPosition(pos);
}

void Emotion::Draw()
{
    if (!_visible) return;

    _popup.Draw();
    _emotion.Draw();
}