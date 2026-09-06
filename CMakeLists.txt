# Copyright (C) 2026 No name software.

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# This file is part of the 5BW Project.

#########-----PROJECT SETTING-----#########
cmake_minimum_required(VERSION 3.16)
project(5bw VERSION 0.0.2 DESCRIPTION "The fucking game")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generating compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###########################################
#---------------------LUA & SOL2-----------
include(FetchContent)

FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG develop
    UPDATE_DISCONNECTED TRUE
    GIT_SHALLOW TRUE
)
message(STATUS "Fetching sol2 library")
FetchContent_MakeAvailable(sol2)

if(sol2_POPULATED)
    message(STATUS "Removing .git files from sol2 source")
    file(REMOVE_RECURSE "${sol2_SOURCE_DIR}/.git")
endif()

find_package(Lua REQUIRED)
############################################
#-------------------ECS SYSTEM--------------
#-------------------In progress yet---------
# FetchContent_Declare(
#     entt
#     GIT_REPOSITORY https://github.com/skypjack/entt.git
#     GIT_TAG v4.0.0
#     UPDATE_DISCONNECTED TRUE
#     GIT_SHALLOW TRUE
# )
# message(STATUS "Fetching Entt library")
# FetchContent_MakeAvailable(entt)

# if(sol2_POPULATED)
#     message(STATUS "Removing .git files from Entt source")
#     file(REMOVE_RECURSE "${entt_SOURCE_DIR}/.git")
# endif()
###########################################
# ---------------- TARGET SETTING ---------
set(SOURCE_EXE main.cpp
    main.cpp

    core/game.cpp
    core/stateManager.cpp
    core/resourceManager.cpp
    core/bus.cpp

    states/menuState.cpp
    states/mapState.cpp
    states/battleState.cpp
    states/sceneState.cpp

    entities/player.cpp
    entities/spriteV2.cpp
    entities/tree.cpp
    entities/uniqueHitbox.cpp

    gui/gui.cpp
    gui/button.cpp
    gui/guiManager.cpp
    gui/buttonList.cpp
    gui/window.cpp

    misc/mapGenerator.cpp
    misc/configReader.cpp

    misc/ghostTrail.cpp
    misc/floatingText.cpp

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
    battle/targetSelector.cpp 

    battle/bulletEntity.cpp

    map/npcManager.cpp
    map/mapEntity.cpp
    map/npc.cpp

    map/tileTrigger.cpp

    dialog/dialogPopup.cpp
)
add_executable(5bw ${SOURCE_EXE})
set_target_properties(5bw PROPERTIES OUTPUT_NAME "5bw")

target_include_directories(5bw PRIVATE ${CMAKE_SOURCE_DIR})

find_package(ZLIB REQUIRED)
###########################################
target_include_directories(5bw PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(5bw PRIVATE sol2::sol2 ${LUA_LIBRARIES})
target_link_libraries(5bw PRIVATE ZLIB::ZLIB)
# In progress yet
# target_link_libraries(5bw PRIVATE EnTT::EnTT)

target_link_libraries(5bw
    PRIVATE
        raylib
        opengl32
        gdi32
        winmm
        stdc++exp # for std::print
)
############################################
#######---------EMBEDED CONTENT-------######
# For #embed "..." or something
set(EMBED_DIR "") # SET HERE!
if(NOT "${EMBED_DIR}" STREQUAL "")
    target_compile_options(5bw PRIVATE --embed-dir=${EMBED_DIR})
endif()

# RESOURCE FOLDER
set(RESOURCE_DIR "resources") # SET HERE!
if(NOT "${RESOURCE_DIR}" STREQUAL "")
    add_custom_command(TARGET 5bw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_DIR}"
            "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}"
        COMMENT "Copying resources to build directory..."
    )
endif()

# LIB FOLDER
set(LIB_DIR "") # SET HERE!
if(NOT "${EMBED_DIR}" STREQUAL "")
    add_custom_command(TARGET 5bw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}"
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_DIR}"
        COMMENT "Copying libs to build directory..."
    )
endif()

# CONFIG FILE
set(CONFIG_FILE "config.json") # SET HERE!
if(NOT "${CONFIG_FILE}" STREQUAL "")
    add_custom_command(TARGET 5bw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG_FILE}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE}"
        COMMENT "Copying ${CONFIG_FILE} to build directory..."
    )
endif()

# CONFIG DIR
set(CONFIG_DIR "") # SET HERE!
if(NOT "${CONFIG_DIR}" STREQUAL "")
    add_custom_command(TARGET 5bw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG_DIR}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_DIR}"
        COMMENT "Copying configs to build directory..."
    )
endif()
############################################

