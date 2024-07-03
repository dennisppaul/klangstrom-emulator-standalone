# set KLST environment for libraries 
target_compile_definitions(${PROJECT_NAME} PUBLIC KLST_ENV=${KLST_ENV})

# add umgebung
set(UMGEBUNG_PATH "${LIBRARY_PATH}/umgebung") # set path to umgebung library 

option(DISABLE_GRAPHICS "Disable graphic output" OFF)
option(DISABLE_VIDEO "Disable video output" ON)
option(DISABLE_AUDIO "Disable audio output + input" OFF)
option(ENABLE_PORTAUDIO "Enable Portaudio Driver for output + input" OFF)

target_compile_definitions(${PROJECT_NAME} PRIVATE UMGEBUNG_WINDOW_TITLE="${PROJECT_NAME}") # set window title

add_subdirectory(${UMGEBUNG_PATH} ${CMAKE_BINARY_DIR}/umgebung-lib-${PROJECT_NAME})
add_umgebung_libs()

# add other libraries
add_subdirectory(${LIBRARY_PATH}/klangwellen ${CMAKE_BINARY_DIR}/klangwellen-lib-${PROJECT_NAME})
add_subdirectory(${LIBRARY_PATH}/klangstrom-emulator ${CMAKE_BINARY_DIR}/klangstrom-emulator-lib-${PROJECT_NAME})
add_subdirectory(${LIBRARY_PATH}/klangstrom-libraries/Klangstrom ${CMAKE_BINARY_DIR}/klangstrom-lib-${PROJECT_NAME})
add_subdirectory(${LIBRARY_PATH}/klangstrom-libraries/Klangstrom_KLST_EMU ${CMAKE_BINARY_DIR}/klangstrom_KLST_EMU-lib-${PROJECT_NAME})

get_target_property(KLANGSTROM_EMU_INCLUDE_DIRS klangstrom_KLST_EMU INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(klangstrom PUBLIC ${KLANGSTROM_EMU_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE klangwellen klangstrom-emulator klangstrom_KLST_EMU klangstrom)