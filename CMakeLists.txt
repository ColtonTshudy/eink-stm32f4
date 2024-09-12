cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME eink-stm32f4)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    # Add user sources here
    ${CMAKE_HOME_DIRECTORY}/Src/program.c
    ${CMAKE_HOME_DIRECTORY}/User/Examples/EPD_4in2_V2_test.c
    ${CMAKE_HOME_DIRECTORY}/User/Config/DEV_Config.c    
    ${CMAKE_HOME_DIRECTORY}/User/GUI/GUI_Paint.c
    ${CMAKE_HOME_DIRECTORY}/User/e-Paper/EPD_4in2_V2.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font8.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font12.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font12CN.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font16.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font20.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font24.c
    ${CMAKE_HOME_DIRECTORY}/User/Fonts/font24CN.c
    ${CMAKE_HOME_DIRECTORY}/User/Examples/ImageData.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_HOME_DIRECTORY}/User/Config
    ${CMAKE_HOME_DIRECTORY}/User/e-Paper
    ${CMAKE_HOME_DIRECTORY}/User/Examples
    ${CMAKE_HOME_DIRECTORY}/User/Fonts
    ${CMAKE_HOME_DIRECTORY}/User/GUI
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
