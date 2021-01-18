# REVIEW THE FOLLOWING IN ORDER TO COMPILE
#
# 1. if on windows, install vcpkg, use it to install qt5 and set VcpkgPath

cmake_minimum_required(VERSION 3.1.0)

project(rushhour)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Auto handling on qrc resource files
set(CMAKE_AUTORCC ON)

# set Qt Path
if (WIN32)
    set(VcpkgPath "D:/vcpkg/packages")
    set(CMAKE_PREFIX_PATH ${QtPath})
endif (WIN32)

# Find the Qt libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

# Populate a CMake variable with the sources
set(rushhour_SRCS
    src/controllers/rushHour.h
    src/utility/string.h
    src/utility/string.cpp
    src/widgets/boardWidget.cpp
    src/widgets/boardWidget.h
    src/widgets/levelWidget.cpp
    src/widgets/levelWidget.h
    src/widgets/mainWidget.cpp
    src/widgets/mainWidget.h
    src/widgets/mainWindow.cpp
    src/widgets/mainWindow.h
    src/widgets/squareWidget.cpp
    src/widgets/squareWidget.h
    src/car.cpp
    src/car.h
    src/common.h
    src/main.cpp
)

if (WIN32)
    add_executable(rushhour WIN32 ${rushhour_SRCS})
endif (WIN32)

if (UNIX)
    add_executable(rushhour ${rushhour_SRCS})
endif (UNIX)

# Copy Qt debug dlls
if (WIN32)
    configure_file(${VcpkgPath}/qt5-base_x86-windows/debug/bin/Qt5Widgetsd.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Widgetsd.dll COPYONLY)
    configure_file(${VcpkgPath}/qt5-base_x86-windows/debug/bin/Qt5Cored.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Cored.dll COPYONLY)
    configure_file(${VcpkgPath}/qt5-base_x86-windows/debug/bin/Qt5Guid.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Guid.dll COPYONLY)
    configure_file(${VcpkgPath}/harfbuzz_x86-windows/debug/bin/harfbuzz.dll ${CMAKE_CURRENT_BINARY_DIR}/harfbuzz.dll COPYONLY)
    configure_file(${VcpkgPath}/libpng_x86-windows/debug/bin/libpng16d.dll ${CMAKE_CURRENT_BINARY_DIR}/libpng16d.dll COPYONLY)
    configure_file(${VcpkgPath}/zlib_x86-windows/debug/bin/zlibd1.dll ${CMAKE_CURRENT_BINARY_DIR}/zlibd1.dll COPYONLY)
    #configure_file(${VcpkgPath}/icu_x86-windows/debug/bin/icuucd65.dll ${CMAKE_CURRENT_BINARY_DIR}/icuucd65.dll COPYONLY)
    #configure_file(${VcpkgPath}/icu_x86-windows/debug/bin/icuind65.dll ${CMAKE_CURRENT_BINARY_DIR}/icuind65.dll COPYONLY)
    #configure_file(${VcpkgPath}/icu_x86-windows/debug/bin/icudtd65.dll ${CMAKE_CURRENT_BINARY_DIR}/icudtd65.dll COPYONLY)
    configure_file(${VcpkgPath}/pcre2_x86-windows/debug/bin/pcre2-16d.dll ${CMAKE_CURRENT_BINARY_DIR}/pcre2-16d.dll COPYONLY)
    configure_file(${VcpkgPath}/freetype_x86-windows/debug/bin/freetyped.dll ${CMAKE_CURRENT_BINARY_DIR}/freetyped.dll COPYONLY)
    configure_file(${VcpkgPath}/bzip2_x86-windows/debug/bin/bz2d.dll ${CMAKE_CURRENT_BINARY_DIR}/bz2d.dll COPYONLY)
endif (WIN32)

# link the Qt libraries
target_link_libraries(rushhour Qt5::Widgets Qt5::Core)