#[[cmake_minimum_required(VERSION 4.0)
project(G_H_Brew)

set(CMAKE_CXX_STANDARD 14)

include_directories(Windows_Test C:/SFML-2_6_2/SFML-2_6_2/include)
link_directories(C:/SFML-2_6_2/SFML-2_6_2/lib)

add_executable(G_H_Brew
        Windows_Test/App.cpp
        Windows_Test/App.h
        Windows_Test/Audio.cpp
        Windows_Test/Audio.h
        Windows_Test/Bullet.cpp
        Windows_Test/Bullet.h
        Windows_Test/Enemy.cpp
        Windows_Test/Enemy.h
        Windows_Test/main.cpp
        Windows_Test/MainMenu.cpp
        Windows_Test/MainMenu.h
        Windows_Test/Player.cpp
        Windows_Test/Player.h
        Window.cpp)

target_link_libraries(G_H_Brew PUBLIC
        sfml-graphics-d
        sfml-window-d
        sfml-system-d
        sfml-audio-d
)]]

cmake_minimum_required(VERSION 4.0)
project(G_H_Brew)

set(CMAKE_CXX_STANDARD 14)

# Point the SFML_DIR to your local copy of the framework
set(SFML_DIR "C:/SFML")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)
add_definitions(-DSFML_STATIC)

add_executable(G_H_Brew
        Windows_Test/App.cpp
        Windows_Test/App.h
        Windows_Test/Audio.cpp
        Windows_Test/Audio.h
        Windows_Test/Bullet.cpp
        Windows_Test/Bullet.h
        Windows_Test/Enemy.cpp
        Windows_Test/Enemy.h
        Windows_Test/main.cpp
        Windows_Test/MainMenu.cpp
        Windows_Test/MainMenu.h
        Windows_Test/Player.cpp
        Windows_Test/Player.h
        Window.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics-d sfml-audio-d sfml-system-d sfml-window-d)