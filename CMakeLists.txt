cmake_minimum_required(VERSION 3.27.8)
project(si-config-logger VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(
    -Wall
    -Wextra
    -pedantic
    -Werror
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    resources/resources.qrc
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# https://stackoverflow.com/a/65970819
find_package(Tesseract)
if (NOT Tesseract_FOUND)
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET tesseract lept)
    add_library(Tesseract::libtesseract ALIAS PkgConfig::Tesseract)
endif()

set(ORIGIN_YEAR "2023")
string(TIMESTAMP CURRENT_YEAR "%Y")
string(COMPARE EQUAL ${ORIGIN_YEAR} ${CURRENT_YEAR} YEARS_EQUAL)

if(YEARS_EQUAL)
    set(PROJECT_YEAR_RANGE ${ORIGIN_YEAR})
else()
    string(CONCAT PROJECT_YEAR_RANGE ${ORIGIN_YEAR} "-" ${CURRENT_YEAR})
endif()

configure_file(src/configure-files/LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)

add_subdirectory(src)
target_link_libraries(
    si-config-logger PRIVATE
    Qt::Widgets
    MainWindow
)