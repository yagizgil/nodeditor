cmake_minimum_required(VERSION 3.10)
project(NodeEditor VERSION 1.0)


set(CMAKE_PREFIX_PATH C:/Qt/6.3.1/mingw_64)
set(QT_PLUGIN_PATH C:/Qt/6.3.1/mingw_64/plugins/platforms)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
    src/NodeEditor.cpp 
    src/node/node.cpp
    src/node/content.cpp
    src/node/socket.cpp
    src/connection.cpp
)

add_library(nodeeditor ${SOURCES})

if(WIN32)
    target_compile_definitions(nodeeditor PRIVATE MY_LIBRARY_EXPORTS)
    set_target_properties(nodeeditor PROPERTIES SUFFIX ".dll")
else()
    # Diğer platformlar için gerekli ayarlar
endif()

target_link_libraries(nodeeditor PRIVATE Qt6::Widgets)
target_include_directories(nodeeditor PRIVATE "${CMAKE_SOURCE_DIR}/include")


add_subdirectory(test)
