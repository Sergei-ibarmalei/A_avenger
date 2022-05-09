cmake_minimum_required(VERSION 3.16.3)
project(main)
set(SOURCES

        video_engine/video_engine.cpp
        classes/texture.cpp
        classes/image_texture.cpp
        classes/text_texture.cpp
        classes/hero.cpp
        classes/alien_stright_one.cpp
        classes/star.cpp
        classes/back_fon.cpp
        classes/laser.cpp
        engine/engine.cpp
        engine/myrand.cpp
        engine/crossing.cpp
        main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
            PRIVATE
            SDL2
            SDL2_image
            SDL2_ttf)
target_compile_options(${PROJECT_NAME} PRIVATE
$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3 -Wall -Wextra -Wpedantic >)
