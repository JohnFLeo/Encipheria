cmake_minimum_required(VERSION 4.2)
project(cipher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#Add Coverage setting
option(ENABLE_COVERAGE "Enable code coverage measurement" OFF)
if(ENABLE_COVERAGE)
    # -O0: Deaktiviert Optimierungen, damit die Zeilen im Bericht exakt stimmen
    # -g:  Fügt Debug-Symbole hinzu
    # --coverage: Aktiviert die Code-Coverage-Instrumentierung (für GCC/Clang)
    add_compile_options(-O0 -g --coverage)
    add_link_options(--coverage)
endif()

enable_testing()
#Testframework
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.15.2 # or a later release
)
FetchContent_MakeAvailable(Catch2)
#Activate CMake support for Catch
include(Catch)
#Define main Project structure
add_library(cipher_core
        src/BigInt.cpp
        src/BigInt.h
)
add_executable(cipher src/main.cpp)
target_link_libraries(cipher PRIVATE cipher_core)
#Define test Project structure
add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE cipher_core Catch2::Catch2WithMain)
#enable discover tests
catch_discover_tests(tests)

