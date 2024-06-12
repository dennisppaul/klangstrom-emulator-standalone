cmake_minimum_required(VERSION 3.12)

project(klangstrom-emulator-standalone)                             # set application name
set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries")           # set path to libraries
set(KLST_ENV 0x46)                                                  # set KLST environment 
                                                                    #  0x46=KLST_PANDA_EMU
                                                                    #  0x47=KLST_CATERPILLAR_EMU

##########################################################
### 1. set compiler flags                              ###
##########################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeCompilerFlags.cmake)

##########################################################
### 2. add source + header files from this directory   ###
##########################################################

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

##########################################################
### 3. add libraries                                   ###
##########################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLibrariesConfig.cmake)
