cmake_minimum_required(VERSION 3.5)

project(Toxy VERSION 1.0 LANGUAGES CXX)

set(BLOCK_SCALE 120)
set(ROWS_COUNT 6)
set(COLLUMNS_COUNT 6)

set(DEBUG ON)
set(AUDIO ON)
set(INFO ON)
set(BUTTONS ON)

set(SDL2_PATH "/usr/include/x86_64-linux-gnu/SDL2")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(STATIC_ASSETS_PATH "${PROJECT_SOURCE_DIR}/static")

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/inc")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

configure_file(config.h.in ${INCLUDE_DIR}/config.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_gfx REQUIRED)

include_directories(
    ${INCLUDE_DIR}
    ${SOURCE_DIR}
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_LIBRARIES}
#    ${SDL2_GFX_LIBRARIES}
)

file(GLOB SOURCE_FILES
    "${SOURCE_DIR}/*.cpp"
)

file(GLOB HEADER_FILES
    "${INCLUDE_DIR}/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} src/table.h)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
#    ${SDL2_GFX_LIBRARIES}
)

if(AUDIO)
    find_package(SDL2_mixer REQUIRED)
    include_directories(${SDL2_MIXER_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
endif(AUDIO)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
