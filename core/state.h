#pragma once

class StateMachine;

class State {
public:
    virtual ~State() = default;

    /**
     * @brief Что стейт делает вначале.
     * @details Например: загрузить текстуры
     */
    virtual void OnEnter() {}

    /**
     * @brief Что стейт делает при выходе
     * @details Например: выгрузить текстуры
     */
    virtual void OnExit() {}

    /**
     * @brief Обработка ввода (клавиатура, мышь и т.д.)
     */
    virtual void HandleInput() = 0;

    /**
     * @brief Логика данного стейта
     * @details Например: задать игроку спид += 1
     * @param dt дельта
     */
    virtual void Update(float dt) = 0;

    /**
     * @brief Отрисовка
     * @warning Только отрисовка. Не изменять состояние игры
     */
    virtual void Draw() = 0;

    void SetStateMachine(StateMachine* sm) {
        stateMachine = sm;
    }

protected:
    StateMachine* stateMachine = nullptr;
};