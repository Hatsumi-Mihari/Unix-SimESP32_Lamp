cmake_minimum_required(VERSION 3.30)
project(ESP32_Render_engine2 C)

set(CMAKE_C_STANDARD 99)

if(PLATFORM STREQUAL "UNIX")
    add_definitions(-DPLATFORM_UNIX)
elseif(PLATFORM STREQUAL "MACOSX_ARM64")
    add_definitions(-DPLATFORM_MACOSX_ARM64)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g -O1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()

add_executable(ESP32_Render_engine2 main.c
        Render_Engine/STL_LIB/List.h
        Render_Engine/STL_LIB/List.c
        Render_Engine/Color_Spaces/RGB888_Struct.h
        Render_Engine/Color_Spaces/HSL.h
        Render_Engine/Color_Spaces/HSL.c
        Render_Engine/main_types/FBO.h
        Render_Engine/main_types/FBO.c
        Render_Engine/STL_LIB/malloc_tracked.c
        Render_Engine/STL_LIB/malloc_tracked.h
        Render_Engine/main_types/Render_State.h
        Render_Engine/main_types/Device.c
        Render_Engine/main_types/Device.h
        Render_Engine/STL_LIB/timer_manager.c
        Render_Engine/STL_LIB/timer_manager.h
        Render_Engine/main_types/Debuger_CLI.c
        Render_Engine/main_types/Debuger_CLI.h
        "Render_Engine/GXF/GFX_Animation_core/GFX_Animation_core.c"
        "Render_Engine/GXF/GFX_Animation_core/GFX_Animation_core.h"
        Render_Engine/GXF/GFX_Functions/GFX_Functions_Pixel.c
        Render_Engine/GXF/GFX_Functions/GFX_Functions_Pixel.h
        Render_Engine/GXF/GFX_Functions/Shaders/ColorFill.c
        Render_Engine/GXF/GFX_Functions/Shaders/ColorFill.h
        Render_Engine/GXF/PipeLine_rendering.c
        Render_Engine/GXF/PipeLine_rendering.h
        Render_Engine/GXF/GFX_Animation_core/Animations/Rainbow.c
        Render_Engine/GXF/GFX_Animation_core/Animations/Rainbow.h
        Render_Engine/GXF/GFX_Animation_core/Animations/Animations.h
        "Network /INet.c"
        "Network /INet.h"
)

