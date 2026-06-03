#include "dialogPopup.h"
#include <cstdio>

std::vector<std::string> DialogPopUp::text;


void DialogPopUp::Show(const SpriteV2* entity, uint32_t dialogID)
{
    text = ConfigReader::GetDialogFromConfig(dialogID);

    if (!text.empty())
    {
        for (std::string str : text) {
            printf((str + '\n').c_str());
        }
    }
}

void DialogPopUp::Next()
{

}