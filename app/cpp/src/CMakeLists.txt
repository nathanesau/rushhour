if (WIN32)
    # Qt Settings
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    # set Qt Path
    set(VcpkgPath "D:/vcpkg/packages")
    set(CMAKE_PREFIX_PATH ${QtPath})

    # Find the Qt libraries
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Core REQUIRED)

    add_library(rushhourlib
        controllers/rushHour.h
        utility/string.h
        utility/string.cpp
        car.cpp
        car.h
        common.h
        levels.h
    )

    add_executable(rushhour WIN32
        widgets/boardWidget.cpp
        widgets/boardWidget.h
        widgets/levelWidget.cpp
        widgets/levelWidget.h
        widgets/mainWidget.cpp
        widgets/mainWidget.h
        widgets/mainWindow.cpp
        widgets/mainWindow.h
        widgets/squareWidget.cpp
        widgets/squareWidget.h
        widgets/widgets.h
        main.cpp
    )

    # Copy Qt debug dlls
    configure_file(${VcpkgPath}/qt5-base_x86-windows/debug/bin/Qt5Widgetsd.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Widgetsd.dll COPYONLY)
    configure_file(${VcpkgPath}/qt5-base_x86-windows/debug/bin/Qt5Cored.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Cored.dll COPYONLY)
    configure_file(${VcpkgPath}/qt5-base_x86-windows/debug/bin/Qt5Guid.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Guid.dll COPYONLY)
    configure_file(${VcpkgPath}/harfbuzz_x86-windows/debug/bin/harfbuzz.dll ${CMAKE_CURRENT_BINARY_DIR}/harfbuzz.dll COPYONLY)
    configure_file(${VcpkgPath}/libpng_x86-windows/debug/bin/libpng16d.dll ${CMAKE_CURRENT_BINARY_DIR}/libpng16d.dll COPYONLY)
    configure_file(${VcpkgPath}/zlib_x86-windows/debug/bin/zlibd1.dll ${CMAKE_CURRENT_BINARY_DIR}/zlibd1.dll COPYONLY)
    configure_file(${VcpkgPath}/pcre2_x86-windows/debug/bin/pcre2-16d.dll ${CMAKE_CURRENT_BINARY_DIR}/pcre2-16d.dll COPYONLY)
    configure_file(${VcpkgPath}/freetype_x86-windows/debug/bin/freetyped.dll ${CMAKE_CURRENT_BINARY_DIR}/freetyped.dll COPYONLY)
    configure_file(${VcpkgPath}/bzip2_x86-windows/debug/bin/bz2d.dll ${CMAKE_CURRENT_BINARY_DIR}/bz2d.dll COPYONLY)

    # link the Qt libraries
    target_link_libraries(rushhour LINK_PUBLIC Qt5::Widgets Qt5::Core rushhourlib)
endif (WIN32)

if (UNIX)
    add_library(rushhourlib 
        controllers/rushHour.h
        utility/string.h
        utility/string.cpp
        car.cpp
        car.h
        common.h
        levels.h
    )
endif (UNIX)
