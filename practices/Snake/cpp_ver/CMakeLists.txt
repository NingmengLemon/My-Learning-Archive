cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Snake VERSION 1.0)

add_subdirectory(Eseq)
add_subdirectory(Kbinput)

# add the executable
add_executable(${PROJECT_NAME} main.cpp game.cpp ui.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC Eseq)
target_link_libraries(${PROJECT_NAME} PUBLIC Kbinput)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/Eseq
                           ${PROJECT_SOURCE_DIR}/Kbinput
                           )