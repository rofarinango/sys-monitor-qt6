cmake_minimum_required(VERSION 3.16)
project(membot-qt6 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Add source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/systemmonitor.cpp
    src/process.cpp
    src/processor.cpp
    src/system.cpp
    src/linux_parser.cpp
    src/format.cpp
)

# Add header files
set(HEADERS
    include/mainwindow.h
    include/systemmonitor.h
    include/process.h
    include/processor.h
    include/system.h
    include/linux_parser.h
    include/format.h
)

# Create executable
add_executable(membot-qt6 ${SOURCES} ${HEADERS})

# Add include directory
target_include_directories(membot-qt6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link Qt libraries
target_link_libraries(membot-qt6 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
) 