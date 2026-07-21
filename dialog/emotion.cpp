#include "emotion.h"
#include "../core/game.h"

void Emotion::Init(const SpriteV2* anchor)
{
    _anchor = anchor;

    TextureResource& tex = Game::GetResources().Get(TextureID::Emotion);
    _defaultEmotionTexture = &tex; // добавлено Клодом

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

    // добавлено Клодом: раньше type тут не использовался вообще (в атлас всегда играл {2,3,4}),
    // теперь реально выбирает кадр/анимацию под конкретную эмоцию. Плюс возврат на дефолтный
    // атлас на случай если до этого был вызван ShowCustom.
    _emotion.SetResource(_defaultEmotionTexture);

    switch (type)
    {
        case EmotionType::Exclaim:
            _emotion.SetAnimation({2, 3, 4}, 0.15f, false);
            break;
        case EmotionType::Confusion:
            _emotion.SetAnimation({11, 12, 13}, 0.2f, true);
            break;
        default:
            _emotion.StopAnimation();
            _emotion.SetFrame(static_cast<size_t>(type));
            break;
    }

    _animationDuration = duration;
    _animationTimer = 0.0f;
    _visible = true;

    _popup.SetAlpha(1.0f);
    _emotion.SetAlpha(1.0f);
}

// добавлено Клодом: слот 15 в emotionPack.png оставлен пустым специально под это,
// но сюда можно передать вообще любую текстуру, не только из атласа
void Emotion::ShowCustom(TextureResource* customTexture, PopupSize size, float duration)
{
    _popup.SetAnimation({0, 1}, 0.15f, false);

    _emotion.StopAnimation();
    _emotion.SetResource(customTexture);
    _emotion.SetSize({48.0f, 48.0f});

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