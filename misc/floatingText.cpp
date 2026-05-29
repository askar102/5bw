#include "FloatingText.h"

void FloatingText::SetFollowOffset(Vector2 offset)
{
    _followOffset = offset;
}

void FloatingText::Show(const std::string& text, Vector2 origin, float lifetime, Color color)
{
    Instance inst;
    inst.text = text;

    inst.pos = {
        origin.x + _followOffset.x,
        origin.y + _followOffset.y
    };

    inst.velocity = {0.0f, -60.0f};
    inst.lifetime = lifetime;
    inst.color = color;

    _texts.push_back(inst);
}

void FloatingText::Update(float dt)
{
    for (auto& t : _texts)
    {
        t.time += dt;

        t.pos.x += t.velocity.x * dt;
        t.pos.y += t.velocity.y * dt;

        t.velocity.y *= 0.98f;
    }

    // удаляем просроченные
    std::erase_if(_texts, [](const Instance& t)
    {
        return t.time >= t.lifetime;
    });
}

void FloatingText::Draw()
{
    for (auto& t : _texts)
    {
        float alpha = 1.0f - (t.time / t.lifetime);
        if (alpha < 0.0f) alpha = 0.0f;

        Color c = t.color;
        c.a = (unsigned char)(255 * alpha);

        DrawText(
            t.text.c_str(),
            (int)t.pos.x,
            (int)t.pos.y,
            20,
            c
        );
    }
}