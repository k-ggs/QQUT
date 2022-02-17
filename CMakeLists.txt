CMAKE_MINIMUM_REQUIRED(VERSION 3.21)

project(QQUT VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_compile_definitions(QML_IMPORT_PATH="${CMAKE_SOURCE_DIR}/assets/")
#add_compile_definitions(QML_DESIGNER_IMPORT_PATH="${CMAKE_SOURCE_DIR}/assets/")
#set(trtdImport "file:///${CMAKE_SOURCE_DIR}" CACHE STRING " import path")
#add_compile_definitions(TRTDImport="${trtdImport}")
#add_compile_definitions(qmlPath="file:///${CMAKE_CURRENT_SOURCE_DIR}/assets/qml/")
find_package(Qt6 6.2 REQUIRED COMPONENTS
    Quick
    Qml
    Gui
    Widgets
    Charts
    Core
    OpenGL
    QuickControls2
    LinguistTools
    REQUIRED
    )
find_package(Glog   REQUIRED)
find_package(spdlog REQUIRED)
find_package(folly  REQUIRED)

add_subdirectory(3rdpart/libmodbus)
add_subdirectory(3rdpart/libserialport)
add_subdirectory(3rdpart/json)

set(
    libs
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
    Qt6::Core
    Qt6::QuickControls2
    Qt6::OpenGL
    glog::glog
    Folly::folly
    spdlog::spdlog
    libserialport::libserialport
    libmodbus::libmodbus
    )
#project_trans
set(
    trans
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/translations/de.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/translations/en.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/translations/es.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/translations/ru.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/translations/zh.ts
    )
#project_UIRCC
set(
    UIRCC
  #  UIRCC.qrc
    assets.qrc
    )
#project_src
include_directories(
    src/Misc/
    src/IO/
    src/IO/serial/
    src/IO/modbusTCP/
    src/IO/modbusRTU/
    src/IOimplement/

    3rdpart/libserialport/
    3rdpart/libmodbus/src/
    3rdpart/libmodbus/src/
    3rdpart/json/single_include/nlohmann/
    )
FILE(
    GLOB
    head_fils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Misc/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/serial/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/modbusTCP/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/modbusRTU/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IOimplement/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DataCenter/*h
    )
FILE(
    GLOB
    source_files
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Misc/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/serial/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/modbusTCP/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/modbusRTU/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IOimplement/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DataCenter/*cpp
    )
qt_add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${qttrans}
    ${UIRCC}
    ${head_fils}
    ${source_files}
    )
qt_create_translation(
    qttrans
    ${trans}
    )
target_compile_definitions(  ${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ${libs}
    )
add_subdirectory(test)





























#CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
#project(libserialport VERSION 3.1.7 LANGUAGES C)
#add_definitions(-DLIBSERIALPORT_MSBUILD)
#set(

#   serial_head
#   libserialport.h
#   libserialport_internal.h
#)

#set(

#   serial_source
#   serialport.c
#   timing.c
#   windows.c
#)

#add_library(libserialport SHARED
#${serial_head}
#${serial_source}
#)
#target_link_libraries(
#    libserialport
#    PUBLIC
#    setupapi.lib

#    )
#add_library(libserialport::libserialport  ALIAS libserialport )



#CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
#project(libmodbus VERSION 3.1.7 LANGUAGES C)

#file(
#    GLOB
#modbus_head
#    src/*.h
#    src/win32/*.h
#)
#include_directories(
#    src/
#    src/win32/
#    )
#file(
#    GLOB
#   modbus_source
#    src/*.c
#    src/win32/*c
#)

#add_library(libmodbus SHARED
#${modbus_head}
#${modbus_source}
#)
#target_link_libraries(
#    libmodbus
#    PUBLIC
# ws2_32.dll
#    )
#add_library(libmodbus::libmodbus  ALIAS libmodbus )



