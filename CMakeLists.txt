cmake_minimum_required(VERSION 3.5.1)

project("Indie Studio")

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

find_package(X11)
find_package(OpenGL)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
endif()

if (APPLE)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib /usr/local/lib/)
endif (APPLE)

if (UNIX)
    find_package(Lua)
    include_directories(/usr/include)
    link_directories(/usr/lib /usr/lib/x86_64-linux-gnu/)
endif (UNIX)

if (WIN32)
    include_directories(
            $ENV{IRRLICHT_PATH_INCLUDE}
            $ENV{IRRKLANG_PATH_INCLUDE}
            $ENV{LUA_PATH_INCLUDE}
    )
    link_directories(
            $ENV{IRRLICHT_PATH_LIB}
            $ENV{IRRKLANG_PATH_LIB}
            $ENV{LUA_PATH_LIB}
    )
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Werror -std=c++14 -g")
    include_directories(${IRRLICHT_PATH_INCLUDE})
    link_directories(${IRRLICHT_PATH_LIB})
endif (WIN32)

include_directories(
        ${X11_INCLUDE_DIR}
        include/Entities
        include/Environment
        include/UI
        include/Core
)

file(
        GLOB
        SRCS
        src/main.cpp
        src/Core/ResourceManager.cpp
        src/Entities/Bomb.cpp
        src/Entities/AEntity.cpp
        src/Core/SaveManager.cpp
        src/Core/Scene.cpp
        src/UI/Lang.cpp
        src/Core/Window.cpp
        src/Core/Event.cpp
        src/Core/AIManager.cpp
        src/Core/SoundEngine.cpp
        src/Core/BombermanAIManager.cpp
        src/Entities/Player.cpp
        src/Entities/Bomberman.cpp
        src/Core/EventManager.cpp
        src/Environment/Map.cpp
        src/Core/MapGenerator.cpp
        src/Environment/ATile.cpp
        src/Environment/ABiomeTile.cpp
        src/Environment/TileSoftWall.cpp
        src/Environment/TileHardWall.cpp
        src/Environment/TileEmpty.cpp
        src/Entities/Mob.cpp
        src/Entities/MobBomberman.cpp
        src/UI/Menu.cpp
        src/UI/AMenuScreen.cpp
        src/UI/GameMenuScreen.cpp
        src/UI/SettingsScreen.cpp
        src/UI/Settings.cpp
        src/UI/MenuElement.cpp
        src/UI/HUD.cpp
        src/UI/TitleScreen.cpp
        src/UI/VersusConfigScreen.cpp
        src/Entities/ABomberman.cpp
        src/Entities/Bomb.cpp
        src/Environment/TileFire.cpp
        src/Environment/ABonusTile.cpp
        src/Environment/TileBonusSpeed.cpp
        src/Environment/TileBonusRange.cpp
        src/Environment/TileBonusBomb.cpp
        src/Environment/BiomeManager.cpp
        src/Core/IndieExceptions.cpp
        src/Environment/TileBonusPassSoftWall.cpp
        src/Environment/TileBonusKick.cpp
        src/Environment/TileBonusRedBomb.cpp
        src/Environment/TileBonusShield.cpp
        src/Environment/TileEgg.cpp
        src/Entities/Mount.cpp
        src/Core/JoystickManager.cpp
        src/Entities/FallingBlock.cpp
        src/Environment/TileBonusRangeMax.cpp
        src/Environment/TileBonusSkull.cpp
        src/Environment/TileGate.cpp
)

file(
        GLOB
        HDRS
        include/Core/ResourceManager.hpp
        include/Entities/Bomb.hpp
        include/Entities/AEntity.hpp
        include/Core/SaveManager.hpp
        include/Core/Scene.hpp
        include/Core/Window.hpp
        include/Core/Event.hpp
        include/Core/SoundEngine.hpp
        include/Core/AIManager.hpp
        include/Core/BombermanAIManager.hpp
        include/Entities/Player.hpp
        include/Entities/Bomberman.hpp
        include/Core/EventManager.hpp
        include/Environment/Map.hpp
        include/Core/MapGenerator.hpp
        include/Core/GameMode.hpp
        include/Environment/ATile.hpp
        include/Environment/ITile.hpp
        include/Environment/ABiomeTile.hpp
        include/Environment/TileHardWall.hpp
        include/Environment/TilesoftWall.hpp
        include/Environment/TileEmpty.hpp
        include/Entities/Mob.hpp
        include/Entities/MobBomberman.hpp
        include/Entities/Bomb.hpp
        include/Environment/TileFire.hpp
        include/UI/Menu.hpp
        include/UI/AMenuScreen.hpp
        include/UI/GameMenuScreen.hpp
        include/UI/SettingsScreen.hpp
        include/UI/Settings.hpp
        include/UI/Lang.hpp
        include/UI/MenuElement.hpp
        include/UI/HUD.hpp
        include/UI/TitleScreen.hpp
        include/UI/VersusConfigScreen.hpp
        include/Environment/ABonusTile.hpp
        include/Environment/TileBonusSpeed.hpp
        include/Environment/TileBonusRange.hpp
        include/Environment/TileBonusBomb.hpp
        include/Environment/BiomeManager.hpp
        include/Core/IndieExceptions.hpp
        include/Environment/TileBonusPassSoftWall.hpp
        include/Environment/TileBonusKick.hpp
        include/Environment/TileBonusRedBomb.hpp
        include/Environment/TileBonusShield.hpp
        include/Environment/TileEgg.hpp
        include/Entities/Mount.hpp
        include/Core/JoystickManager.hpp
        include/Entities/FallingBlock.hpp
        include/Environment/TileBonusRangeMax.hpp
        include/Environment/TileBonusSkull.hpp
        include/Environment/TileGate.hpp
)

if (WIN32)
    add_executable(
            bomberman
            ${SRCS}
            ${HDRS}
            ressource.rc
    )
    target_link_libraries(
            bomberman
            lua53
            irrKlang
    )
else()
    add_executable(
            bomberman
            ${SRCS}
            ${HDRS}
    )
    target_link_libraries(
            bomberman
            ${LUA_LIBRARY}
            IrrKlang
    )
endif(WIN32)

target_link_libraries(
        bomberman
        ${X11_LIBRARIES}
        ${OPENGL_LIBRARY}
        Irrlicht
)

if (WIN32)
    add_custom_command(TARGET bomberman POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:bomberman>
            "${PROJECT_SOURCE_DIR}\\build")
    add_custom_command(TARGET bomberman POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}\\libs\\win\\Irrlicht.dll"
            "${PROJECT_SOURCE_DIR}\\build")
    add_custom_command(TARGET bomberman POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}\\libs\\win\\ikpFlac.dll"
            "${PROJECT_SOURCE_DIR}\\build")
    add_custom_command(TARGET bomberman POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}\\libs\\win\\ikpMP3.dll"
            "${PROJECT_SOURCE_DIR}\\build")
    add_custom_command(TARGET bomberman POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}\\libs\\win\\irrKlang.dll"
            "${PROJECT_SOURCE_DIR}\\build")
endif (WIN32)

install(TARGETS bomberman
        RUNTIME DESTINATION share/bomberman/bin)
install(CODE "execute_process(COMMAND sudo cp -r ${PROJECT_SOURCE_DIR}/res /usr/local/share/bomberman)")
install(CODE "execute_process(COMMAND sudo ln -s /usr/local/share/bomberman/bin/bomberman /usr/local/bin/bomberman)")