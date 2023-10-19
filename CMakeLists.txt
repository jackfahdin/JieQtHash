cmake_minimum_required(VERSION 3.5)

project(JieQtHash VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES JieQtHash_zh_CN.ts)

set(CRC_SOURCES
        CRC/CRC.cpp
        CRC/CRC.h
        CRC/CRC12.cpp
        CRC/CRC12.h
        CRC/CRC16.cpp
        CRC/CRC16.h
        CRC/CRC32.cpp
        CRC/CRC32.h
        CRC/CRC64.cpp
        CRC/CRC64.h
        CRC/CRC8.cpp
        CRC/CRC8.h
        CRC/CrcDefines.h
        CRC/CrcFastReverse.cpp
        CRC/CrcFastReverse.h
        CRC/CrcParameters.h
)

## CRC算法
#aux_source_directory(${PROJECT_SOURCE_DIR}/CRC CRC_FILES)
#include_directories("${PROJECT_SOURCE_DIR}/CRC")

set(PROJECT_SOURCES
        main.cpp
        jieqthashwidget.cpp
        jieqthashwidget.h
        jieqthashwidget.ui
        ${TS_FILES}
        filehashthread.cpp
        filehashthread.h
        ${CRC_SOURCES}
        logo.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(JieQtHash
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET JieQtHash APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(JieQtHash SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(JieQtHash
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(JieQtHash PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.JieQtHash)
endif()
set_target_properties(JieQtHash PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS JieQtHash
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(JieQtHash)
endif()
