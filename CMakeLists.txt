cmake_minimum_required(VERSION 3.5)
project(Furnix LANGUAGES CXX)

# Qt setup
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_compile_definitions(
    _UNICODE
    UNICODE
    MUP_USE_WIDE_STRING
)

# MuParser dependency
set(ENABLE_SAMPLES OFF)
set(BUILD_SHARED_LIBS OFF)
set(ENABLE_WIDE_CHAR OFF)
set(ENABLE_OPENMP ON)
add_subdirectory(3dpart/muparser-2.3.5)

# yaml-cpp dependency
include(FetchContent)
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)


file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.cc" 
    "src/*.c"
)

file(GLOB_RECURSE HEADERS 
    "src/*.h" 
    "src/*.hpp"
)

file(GLOB_RECURSE FORMS 
    "src/*.ui"
)

file(GLOB_RECURSE RESOURCES 
    "resources/*.qrc"
)

# Executable setup
qt_add_executable(${PROJECT_NAME}
    WIN32
    MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
    main.cpp
    methods/ledebour_method.yaml
    methods/pavlov_method.yaml
)

target_include_directories(Furnix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Furnix PRIVATE
    Qt::Core
    Qt::Widgets
    yaml-cpp::yaml-cpp
    muparser::muparser
)

add_custom_command(
    TARGET Furnix POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/methods"
        "$<TARGET_FILE_DIR:Furnix>/methods"
)

# Installation
include(GNUInstallDirs)
install(TARGETS Furnix
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Furnix
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Furnix PRIVATE _DEBUG)
    target_compile_options(Furnix PRIVATE -O0 -Wall -ggdb3)
else()
    target_compile_definitions(Furnix PRIVATE NDEBUG)
    target_compile_options(Furnix PRIVATE -O3 -Wall)
endif()