cmake_minimum_required(VERSION 3.16)

project(ClientChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 1. C++20 for coroutine support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Add 'Network' to the REQUIRED COMPONENTS
<<<<<<< HEAD
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Qml Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Qml Quick)
=======
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)
>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8

# 3. QCoro download and configuration block
include(FetchContent)
set(USE_QT_VERSION ${QT_VERSION_MAJOR} CACHE STRING "Compile QCoro with Qt${QT_VERSION_MAJOR}")

# Turn off EVERYTHING except Core and Network to ensure cross-platform compatibility
<<<<<<< HEAD
set(QCORO_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(QCORO_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(QCORO_WITH_QTDBUS OFF CACHE BOOL "" FORCE)
set(QCORO_WITH_QTWEBSOCKETS OFF CACHE BOOL "" FORCE)
set(QCORO_WITH_QTQML OFF CACHE BOOL "" FORCE)
set(QCORO_WITH_QTQUICK OFF CACHE BOOL "" FORCE)
=======
set(QCORO_BUILD_EXAMPLES OFF CACHE BOOL "Don't build QCoro examples" FORCE)
set(QCORO_BUILD_TESTING OFF CACHE BOOL "Don't build QCoro tests" FORCE)
set(QCORO_WITH_QTDBUS OFF CACHE BOOL "Don't build QCoro DBus" FORCE)
set(QCORO_WITH_QTWEBSOCKETS OFF CACHE BOOL "Don't build QCoro WebSockets" FORCE)
set(QCORO_WITH_QTQML OFF CACHE BOOL "Don't build QCoro QML" FORCE)
set(QCORO_WITH_QTQUICK OFF CACHE BOOL "Don't build QCoro Quick" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Disable standard tests" FORCE)
>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8

FetchContent_Declare(
    QCoro
    GIT_REPOSITORY https://github.com/danvratil/qcoro.git
<<<<<<< HEAD
    GIT_TAG v0.13.0
)

FetchContent_MakeAvailable(QCoro)

set(PROJECT_SOURCES
    main.cpp
    client.cpp
    client.h
    client.ui
=======
    GIT_TAG v0.10.0
)
FetchContent_MakeAvailable(QCoro)

set(PROJECT_SOURCES
        main.cpp
        client.cpp
        client.h
        client.ui
>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ClientChat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ClientChat SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ClientChat
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 4. Link the newly added Qt Network and QCoro libraries to your executable
target_link_libraries(ClientChat PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
<<<<<<< HEAD
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Quick
    QCoro6::Core # Note: Depending on your QCoro setup, this might be QCoro5::Core or QCoro6::Core
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ClientChat)
endif()

=======
    QCoro${QT_VERSION_MAJOR}Core
    QCoro${QT_VERSION_MAJOR}Network
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ClientChat)
endif()
>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8
set_target_properties(ClientChat PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ClientChat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ClientChat)
endif()
