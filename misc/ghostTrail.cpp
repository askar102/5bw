#include "ghostTrail.h"

void GhostTrail::Init(int maxGhosts, float fadeSpeed, float interval)
{
    _maxGhosts = maxGhosts;
    _fadeSpeed = fadeSpeed;
    _interval = interval;
}

void GhostTrail::Update(float dt, const SpriteV2& sprite)
{
    if (!_enabled) return;

    // тикаем таймер, если пора — снапшотим позицию
    _timer += dt;
    if (_timer >= _interval)
    {
        _timer = 0.0f;

        GhostFrame frame;
        frame.position = sprite.GetPosition();
        frame.rotation = sprite.GetRotation();
        frame.alpha = 0.6f; // начальная прозрачность копии

        _frames.push_back(frame);

        if (static_cast<int>(_frames.size()) > _maxGhosts)
            _frames.pop_front();
    }

    // fade out всех копий
    for (auto& frame : _frames)
    {
        frame.alpha -= _fadeSpeed * dt;
        if (frame.alpha < 0.0f)
            frame.alpha = 0.0f;
    }
}

void GhostTrail::Draw(const SpriteV2& sprite) const
{
    if (!_enabled) return;

    // рисуем от старых к новым, новые поверх
    for (const auto& frame : _frames)
    {
        if (frame.alpha <= 0.0f) continue;

        // временно меняем позицию и альфу через const_cast — не трогаем оригинал
        SpriteV2 ghost = sprite; // копируем спрайт (дёшево, нет текстур внутри)
        ghost.SetPosition(frame.position);
        ghost.SetRotation(frame.rotation);
        ghost.SetAlpha(frame.alpha);

        
        ghost.Draw();
    }
}