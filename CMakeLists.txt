cmake_minimum_required(VERSION 3.16)
project(5bw12)

set(CMAKE_CXX_STANDARD 17)

# исходники
add_executable(5bw12
    main.cpp

    core/Game.cpp
    core/stateMachine.cpp

    states/menuState.cpp
    states/mapState.cpp
    states/battleState.cpp

    entities/player.cpp
    entities/sprite.cpp

    misc/mapGenerator.cpp

    battle/battleSystem.cpp
    battle/battleEntity.cpp
    battle/actionText.cpp
    battle/abilityPanel.cpp
    battle/battleResources.cpp
    battle/party.cpp
    battle/ability.cpp
    battle/abilityManager.cpp
    battle/vfx.cpp
    battle/cardVfx.cpp
    battle/vfxManager.cpp
)

# include пути (чтобы #include "game.h" работал)
target_include_directories(5bw12 PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# raylib (если установлен в системе)
target_link_libraries(5bw12
    raylib
    opengl32
    gdi32
    winmm
)
