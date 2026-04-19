src/
 ├── core/
 │    ├── Game.h / Game.cpp        // главный цикл
 │    ├── State.h                 // интерфейс сцен
 │    ├── StateMachine.h/cpp      // переключение сцен
 │
 ├── engine/
 │    ├── Input.h/cpp            // ввод
 │    ├── Time.h/cpp             // dt, таймеры
 │    ├── Assets.h/cpp           // загрузка текстур/звуков
 │
 ├── world/
 │    ├── MapState.h/cpp         // карта (overworld)
 │    ├── BattleState.h/cpp      // бой
 │    ├── MenuState.h/cpp        // меню
 │
 ├── entities/
 │    ├── Entity.h               // базовый объект
 │    ├── Player.h/cpp
 │    ├── Enemy.h/cpp
 │
 ├── components/ (если захочешь ECS позже)
 │
 ├── gui/
 │    ├── Button.h/cpp
 │    ├── Panel.h/cpp
 │
 └── main.cpp

 project/
 ├── core/
 │    ├── game.h / Game.cpp        
 │    ├── state.h                 
 │    ├── stateMachine.h/cpp      
 │   
 ├── states/
 │    ├── menuState.cpp / menuState.h    
 │  
 └── main.cpp


 if (CheckCollisionRecs(player.getRect(), enemy.getRect())) {
    // battle
}