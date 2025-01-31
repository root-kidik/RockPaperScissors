add_executable(${PROJECT_NAME} Main.cpp)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Network)

if(WIN32)
    find_package(Qt6 COMPONENTS QWindowsIntegrationPlugin REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::QWindowsIntegrationPlugin)
endif()