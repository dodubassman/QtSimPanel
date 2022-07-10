# This file is a copy/paste from Qt manual
# see: https://doc.qt.io/qt-5/cmake-manual.html

cmake_minimum_required(VERSION 3.16)

project(SimPanel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED Qml Widgets)

add_executable(SimPanel
  src/datastore.cpp
  src/KeyReceiver.cpp
  src/main.cpp
  src/qml.qrc
  src/QtSimPanel.cpp
  src/xplaneudpclient.cpp
)

target_link_libraries(SimPanel Qt5::Qml Qt5::Widgets)
