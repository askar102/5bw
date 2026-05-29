cmake_minimum_required(VERSION 3.16)
project(5bw12)

set(CMAKE_CXX_STANDARD 23)

# исходники
add_executable(5bw12
    main.cpp

    core/game.cpp
    core/stateManager.cpp
    core/resourceManager.cpp

    states/menuState.cpp
    states/mapState.cpp
    states/battleState.cpp

    entities/player.cpp
    entities/spriteV2.cpp
    entities/tree.cpp
    entities/mapEntity.cpp

    gui/gui.cpp
    gui/button.cpp
    gui/guiManager.cpp
    gui/buttonList.cpp

    misc/mapGenerator.cpp
    misc/configReader.cpp

    misc/ghostTrail.cpp

    battle/battleEntity.cpp
    battle/actionText.cpp
    battle/abilityPanel.cpp
    
    battle/party.cpp
    battle/playerParty.cpp
    battle/enemyParty.cpp

    battle/partyManager.cpp

    battle/ability.cpp
    battle/abilityManager.cpp
    battle/vfx.cpp
    battle/cardVfx.cpp
    battle/vfxManager.cpp

    battle/effectLabel.cpp
    battle/effectIcon.cpp
    battle/effectIconList.cpp

    battle/minigame.cpp
)

# include пути (чтобы #include "game.h" работал)
target_include_directories(5bw12 PRIVATE
    ${CMAKE_SOURCE_DIR}
)

if (WIN32)
    target_link_libraries(5bw12
        raylib
        opengl32
        gdi32
        winmm
    )

elseif (UNIX)
    target_link_libraries(5bw12
        raylib
        m
        pthread
        dl
    )
endif()
