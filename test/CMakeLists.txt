cmake_minimum_required(VERSION 3.10)
project(MyTest)

set(CMAKE_PREFIX_PATH C:/Qt/6.3.1/mingw_64)
set(QT_PLUGIN_PATH C:/Qt/6.3.1/mingw_64/plugins/platforms)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TEST 
    main.cpp
)


add_executable(test ${TEST})


target_link_libraries(test PUBLIC nodeeditor)
target_link_libraries(test PRIVATE Qt6::Widgets)
target_include_directories(test PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(test PRIVATE "${CMAKE_SOURCE_DIR}/include/node")