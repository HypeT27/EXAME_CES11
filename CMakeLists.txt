cmake_minimum_required(VERSION 3.26)

project(EXAME_CES11)

INCLUDE(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(EXAME_CES11 src/Sources/main.cpp
        src/Sources/Game.cpp
        src/Headers/Game.h
        src/States/State.cpp
        src/States/State.h
        src/States/GameState.cpp
        src/States/GameState.h
        src/Entities/Entity.cpp
        src/Entities/Entity.h
        src/Entities/Player.cpp
        src/Entities/Player.h
        src/Entities/Enemy.cpp
        src/Entities/Enemy.h
        src/Entities/enemyBullet.cpp
        src/Entities/enemyBullet.h
        src/Entities/enemyBullet.h
        src/Entities/playerAttack.cpp
        src/Entities/playerAttack.h
        src/GameScene/GameScene.cpp
        src/GameScene/GameScene.h

)

target_link_libraries(EXAME_CES11 sfml-graphics)