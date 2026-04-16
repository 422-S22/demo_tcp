cmake_minimum_required(VERSION 3.16)
project(tcp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network)

add_subdirectory(server)
add_subdirectory(client)