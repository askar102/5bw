#include "vfx.h"

class cardVfx : public Vfx {
public:
    void Update(float dt) override;
    void Draw() const override;
    bool IsFinished() const override;

    // текстура лежит в ../resources/card.png


};