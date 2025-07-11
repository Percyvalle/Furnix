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

# Executable setup
qt_add_executable(${PROJECT_NAME}
    WIN32
    MACOSX_BUNDLE

    main.cpp

    src/view/main_window.cpp
    src/view/main_window.h
    src/view/main_window.ui

    src/core/grid/grid_scene.h
    src/core/grid/grid_scene.cpp

    src/core/canvas/zoom_graphics_view.h
    src/core/canvas/zoom_graphics_view.cpp

    src/models/calculation_method_data.h
    src/models/input_parameters_data.h
    src/models/output_parameters_data.h
    src/models/formula_parameters_data.h

    src/core/yaml/yaml_deserializer.h

    src/scanner/methods_scanner.h
    src/scanner/methods_scanner.cpp

    src/common_constants.h

    src/entity/calculation_method.h
    src/entity/calculation_method.cpp
    src/entity/input_param_method.h
    src/entity/input_param_method.cpp
    src/entity/output_param_method.h
    src/entity/output_param_method.cpp

    src/core/application_controller.h
    src/core/application_controller.cpp
    src/core/furnace_parameter_calculator.h
    src/core/furnace_parameter_calculator.cpp

    src/presenter/main_presenter.h
    src/presenter/main_presenter.cpp

    src/interfaces/i_canvas_view.h
    src/interfaces/i_methods_view.h
    src/interfaces/i_main_window_view.h
    src/interfaces/i_input_param_view.h

    src/graphics/furnace_profile_item.h
    src/graphics/furnace_profile_item.cpp

    src/entity/furnace_param_method.h
    src/entity/furnace_param_method.cpp

    methods/ledebour_method.yaml
    methods/pavlov_method.yaml

    src/models/furnace_profile_param.h

    src/infrastructure/loaders/furnace_profile_loader.h
    src/infrastructure/loaders/furnace_profile_loader.cpp

    src/graphics/furnace_part_item.h
    src/graphics/furnace_part_item.cpp
    src/graphics/furnace_runner_item.h
    src/graphics/furnace_runner_item.cpp
    src/graphics/furnace_tapping_item.h 
    src/graphics/furnace_tapping_item.cpp
    src/graphics/furnace_bloom_item.h 
    src/graphics/furnace_bloom_item.cpp
    src/graphics/furnace_shoulder_item.h 
    src/graphics/furnace_shoulder_item.cpp
    src/graphics/furnace_shaft_item.h 
    src/graphics/furnace_shaft_item.cpp
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