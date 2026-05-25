#include "../raylib/raylib.h"
#include <algorithm>

class ColorManager {
public:
    static Color ApplyBrightness(Color c, float b);
};