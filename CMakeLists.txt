cmake_minimum_required(VERSION 3.20)

project(calculator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# clang-tidy
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include(FetchContent)

FetchContent_Declare(
    mathlib
    GIT_REPOSITORY https://github.com/timkamosee/math_mosee.git
    GIT_TAG master
)

FetchContent_MakeAvailable(mathlib)

add_executable(calculator
    src/main.cpp
)

# Если библиотека INTERFACE (правильный вариант)
target_link_libraries(calculator PRIVATE math_mosee)

# Установка
install(TARGETS calculator
    RUNTIME DESTINATION bin
)

# clang-format target
find_program(CLANG_FORMAT clang-format)

if(CLANG_FORMAT)

    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/include/*.h
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
    )

endif()

