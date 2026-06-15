cmake_minimum_required(VERSION 3.20)

project(osgearth-flyby)

# Compile osgEarth yourself and put it above root directory of this project
set(osgEarth_DIR "../osgearth/build")
find_package(osgEarth CONFIG REQUIRED)

add_executable(osgearth-flyby
    src/main.cpp
    src/option/Option.cpp
    src/render/Capture.cpp
    src/render/Camera.cpp
    src/render/Context.cpp
    src/output/Memory.cpp
)

target_link_libraries(osgearth-flyby PRIVATE osgEarth::osgEarth)

install(TARGETS osgearth-flyby RUNTIME DESTINATION bin)
