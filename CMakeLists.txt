cmake_minimum_required(VERSION 3.12)

project(klangstrom-emulator-standalone)                             # set application name
set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries")           # set path to libraries
set(KLST_ENV 0x46)                                                  # set KLST environment 
                                                                    #     0x46=KLST_PANDA_EMU
                                                                    #     0x47=KLST_CATERPILLAR_EMU

#set(SOURCE_FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCE_FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/klangstrom-libraries/Klangstrom/examples/SerialDevice") # for development purposes

##########################################################
### 1. set compiler flags                              ###
##########################################################

include(${LIBRARY_PATH}/CMakeCompilerFlags.cmake)

##########################################################
### 2. add source + header files from this directory   ###
##########################################################

include_directories("${SOURCE_FILES_DIR}")
file(GLOB SOURCE_FILES
        "${SOURCE_FILES_DIR}/*.c"
        "${SOURCE_FILES_DIR}/*.cpp"
        "${SOURCE_FILES_DIR}/*.ino"
)
set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
foreach(ino_file ${SOURCE_FILES})
    if (ino_file MATCHES "\\.ino$")
        set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x c++")
    endif()
endforeach()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

##########################################################
### 3. add libraries                                   ###
##########################################################

include(${LIBRARY_PATH}/CMakeLibrariesConfig.cmake)

##########################################################
### 4. add custom target to run application            ###
### ( OPTIONAL )                                       ###
##########################################################

add_custom_target(run
    DEPENDS ${PROJECT_NAME}
    COMMENT "Building and running ${PROJECT_NAME}..."
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)

##########################################################
### some helpful commands                              ###
##########################################################

# configure: cmake -B build
# built    : cmake --build build
# run      : cmake --build build --target run
# clean    : rm -r build
