#include "colorManager.h"

Color ColorManager::ApplyBrightness(Color c, float b)
{
    c.r = (unsigned char)std::min(255.0f, c.r * b);
    c.g = (unsigned char)std::min(255.0f, c.g * b);
    c.b = (unsigned char)std::min(255.0f, c.b * b);
    return c;
}