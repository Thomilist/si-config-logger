add_library(DeviceData DeviceData.cpp)
target_link_libraries(
    DeviceData PRIVATE
    Qt::Widgets
    OcrField
)

add_library(HistoryTableModel HistoryTableModel.cpp)
target_link_libraries(
    HistoryTableModel PRIVATE
    Qt::Widgets
    DeviceData
    OcrField
)

set_source_files_properties(
    MainWindow.cpp OBJECT_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Fields.hpp
)
add_library(MainWindow MainWindow.cpp)
target_link_libraries(
    MainWindow PRIVATE
    Qt::Widgets
    DeviceData
    HistoryTableModel
    OcrField
    Screenshot
    Settings
)

add_library(OcrField OcrField.cpp)
target_link_libraries(
    OcrField PRIVATE
    Qt::Widgets
    OcrWorker
)

add_library(OcrWorker OcrWorker.cpp)
target_link_libraries(
    OcrWorker PRIVATE
    Qt::Widgets
    TessApi
)

add_library(Screenshot Screenshot.cpp)
target_link_libraries(
    Screenshot PRIVATE
    Qt::Widgets
)

add_library(Settings Settings.cpp)
target_link_libraries(
    Settings PRIVATE
    Qt::Widgets
)

add_library(TessApi TessApi.cpp)
target_link_libraries(
    TessApi PRIVATE
    Qt::Widgets
    Tesseract::libtesseract
)