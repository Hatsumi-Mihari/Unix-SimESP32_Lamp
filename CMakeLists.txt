cmake_minimum_required(VERSION 3.31)
project(ESP32_Render_engine2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-15)

add_executable(ESP32_Render_engine2 main.c
        Render_Engine/STL_LIB/List.h
        Render_Engine/STL_LIB/List.c
        Render_Engine/Color_Spaces/RGB888_Struct.h
        Render_Engine/Color_Spaces/HSL.h
        Render_Engine/Color_Spaces/HSL.c
        Render_Engine/main_types/FBO.h
        Render_Engine/main_types/FBO.c
        Render_Engine/config.h
        Render_Engine/STL_LIB/malloc_tracked.c
        Render_Engine/STL_LIB/malloc_tracked.h
        Render_Engine/main_types/Render_State.h
        Render_Engine/main_types/Device.c
        Render_Engine/main_types/Device.h
        Render_Engine/STL_LIB/timer_manager.c
        Render_Engine/STL_LIB/timer_manager.h
        Render_Engine/main_types/Debuger_CLI.c
        Render_Engine/main_types/Debuger_CLI.h
)

