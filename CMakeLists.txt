cmake_minimum_required(VERSION 3.14)
project(GameRpg LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(NOT DEFINED CMAKE_CXX_FLAGS_RELEASE)
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

if(NOT DEFINED CMAKE_CXX_FLAGS_DEBUG)
  set(CMAKE_CXX_FLAGS_DEBUG "-g2 -ggdb")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_TTF REQUIRED)

include(lib/cmake/CPM.cmake)

add_executable(${PROJECT_NAME} src/algorithm.cpp
  src/board.cpp
  src/classes.cpp
  src/combat.cpp
  src/entity.cpp
  src/entity_spawn.cpp
  src/game.cpp
  src/game_function.cpp
  src/input.cpp
  src/mob.cpp
  src/player.cpp
  src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL2::SDL2
  SDL2_ttf::SDL2_ttf
  SDL2_image::SDL2_image)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

# These could be stored in the executable with ar
file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

install(
  DIRECTORY headers/
  DESTINATION include/gamerpg
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  enable_testing()
  CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.14.0
    VERSION 1.14.0
    OPTIONS "INSTALL_GTEST OFF" "BUILD_GMOCK OFF" "BUILD_GMOCK OFF" "gtest_force_shared_crt"
  )
endif()
