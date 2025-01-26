cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp 
                    src/include/opening_scene.cpp src/include/dressing_scene.cpp src/include/ending_scene.cpp src/include/scene.h 
                    src/include/button.cpp src/include/phone.cpp src/include/clothes_selector.cpp src/include/object.h
                    src/include/helpers.cpp src/include/helpers.h)
target_compile_features(main PRIVATE cxx_std_17)
find_package(cpplocate REQUIRED)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio PUBLIC cpplocate::cpplocate)
target_include_directories(main PRIVATE src/include)
