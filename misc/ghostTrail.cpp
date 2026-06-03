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

    _timer += dt;
    if (_timer >= _interval)
    {
        _timer = 0.0f;

        GhostFrame frame;
        frame.position = sprite.GetPosition();
        frame.rotation = sprite.GetRotation();
        frame.alpha = 0.6f;

        _frames.push_back(frame);

        if (static_cast<int>(_frames.size()) > _maxGhosts)
            _frames.pop_front();
    }

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

    for (const auto& frame : _frames)
    {
        if (frame.alpha <= 0.0f) continue;

        SpriteV2 ghost = sprite; 
        ghost.SetPosition(frame.position);
        ghost.SetRotation(frame.rotation);
        ghost.SetAlpha(frame.alpha);

        
        ghost.Draw();
    }
}