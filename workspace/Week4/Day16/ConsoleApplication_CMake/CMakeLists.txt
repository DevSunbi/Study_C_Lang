cmake_minimum_required(VERSION 3.19)
project(ConsoleApplication_CMake LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core LinguistTools)

qt_standard_project_setup()

qt_add_executable(ConsoleApplication_CMake
    main.cpp
)

qt_add_translations(
    TARGETS ConsoleApplication_CMake
    TS_FILES ConsoleApplication_CMake_ko_KR.ts
)

target_link_libraries(ConsoleApplication_CMake
    PRIVATE
        Qt::Core
)

install(TARGETS ConsoleApplication_CMake
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
