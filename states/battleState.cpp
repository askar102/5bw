#include "battleState.h"

void BattleState::HandleInput()
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (Ability* clickedAbility = _abilityPanel.GetAbilityAt(mouse))
        {
            _character->selected = false;

            const Vector2 casterPos = _character->getSprite().getPosition();
            const Vector2 targetPos = _enemy->getSprite().getPosition();
            const std::string abilityName = clickedAbility->getName();

            const float casterHeight = _character->getSprite().getRect().height;

            if (abilityName == "Attack")
            {
                /**
                 * TODO: maybe we should pass _character itself
                 * 
                 */
                _vfxManager.SpawnCardVfx(casterPos, casterHeight);
            }

            clickedAbility->Execute(*_character, *_enemy);
            _character->actionText.Add(TextFormat("Used %s", clickedAbility->getName().c_str()), YELLOW);
            _enemy->actionText.Add(TextFormat("Hit by %s", clickedAbility->getName().c_str()), ORANGE);
            return;
        }

        if (CheckCollisionPointRec(mouse, _character->getSprite().getRect()))
        {
            if (_character->canSelected)
            {
                _character->selected = !_character->selected;
            }
        }
        else
        {
            _character->selected = false;
        }
    }

    if (IsKeyPressed(KEY_H))
    {
        Sprite::SetDrawHitboxes(!Sprite::GetDrawHitboxes());
    }
}

void BattleState::Draw()
{
    ClearBackground(RED);

    // РЕНДЕР: сначала фон и сущности.
    _background.Draw();
    _character->Draw();
    _enemy->Draw();

    // РЕНДЕР: затем рисуем активные эффекты поверх.
    _vfxManager.Draw();

    _abilityPanel.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
}

void BattleState::Update(float dt)
{
    // UI-ЛОГИКА: панель умений следует за игроком и видна только при выборе.
    _abilityPanel.SetVisible(_character->selected);
    _abilityPanel.SetAnchor(_character->getSprite().getPosition());
    _abilityPanel.Update();

    // ЛОГИКА АНИМАЦИЙ: обновляем таймеры и положение эффектов.
    _vfxManager.Update(dt);
}

void BattleState::OnEnter()
{
    _character = std::make_unique<BattleEntity>();
    _enemy = std::make_unique<BattleEntity>();

    _character->abilities.push_back(std::make_unique<Ability>("Attack", 10, 0));
    _character->abilities.push_back(std::make_unique<Ability>("Defend"));
    _character->abilities.push_back(std::make_unique<Ability>("Heal", 0, 10));

    _resources.Load();

    InitBackground();

    _vfxManager.InitTextureManager(&_resources);

    _character->getSprite().setPosition({50, 300});
    _character->getSprite().setTexture(_resources.CharacterTexture());

    _enemy->getSprite().setPosition({600, 300});
    _enemy->getSprite().setTexture(_resources.EnemyTexture());
    _enemy->canSelected = false;
    _enemy->getSprite().setSize(100, 100);

    _abilityPanel.SetIconTexture(_resources.AbilityIconTexture());
    _abilityPanel.SetAbilities(_character->abilities);
    _abilityPanel.SetAnchor(_character->getSprite().getPosition());
    _abilityPanel.SetVisible(false);
    _abilityPanel.Update();
}

void BattleState::OnExit()
{
    _vfxManager.Clear();
    _resources.Unload();
}

void BattleState::InitBackground()
{
    _background.setTexture(_resources.BackgroundTexture());
    _background.setSize(800, 600);
    _background.SetCanDrawHiboxes(false);
}
