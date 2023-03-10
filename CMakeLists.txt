cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MiniEngine)

option(PLATFORM_WINDOWS "Build for windows?" ON)

if(PLATFORM_WINDOWS)
    list(APPEND COMPILE_DEFS "PLATFORM_WINDOWS")
    list(APPEND INCLUDES "${PROJECT_SOURCE_DIR}/src/Platforms/Windows")
    list(APPEND SOURCE_FILES src/Platforms/Windows/WindowsWindow.cpp src/Platforms/Windows/WindowsWindow.h)
    list(APPEND LIBS gdi32 user32)
else()
    list(APPEND INCLUDES "${PROJECT_SOURCE_DIR}/src/Platforms/Linux")
    list(APPEND SOURCE_FILES src/Platforms/Linux/LinuxWindow.cpp src/Platforms/Linux/LinuxWindow.h)
    list(APPEND LIBS X11)
endif()

list(APPEND SOURCE_FILES src/Core/Game.cpp src/Core/Game.h src/Core/EntryPoint.h src/Core/MiniWindow.h src/Core/MiniTime.h src/Core/MiniTime.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${COMPILE_DEFS} PUBLIC PROJECT_DIR="${PROJECT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

project(TestGame)
set(SOURCE_FILES TestGame/TestGame.cpp src/Core/MiniEngine.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC src/Core)
target_link_libraries(${PROJECT_NAME} PUBLIC MiniEngine)