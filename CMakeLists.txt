cmake_minimum_required(VERSION 3.5)
project(ImageViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network Multimedia MultimediaWidgets REQUIRED)

# اعمل الـ executable
add_executable(ImageViewer
    main.cpp
    ImageViewer.cpp
    resources.qrc   # هنا تحط الـ qrc على طول (بما إنك عامل AUTORCC)
)

# اربط المكتبات
target_link_libraries(ImageViewer
    Qt5::Widgets
    Qt5::Network
    Qt5::Multimedia
    Qt5::MultimediaWidgets
)
