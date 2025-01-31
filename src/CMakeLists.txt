add_executable(${PROJECT_NAME} Main.cpp)

if(UNIX AND NOT APPLE)
    set(INTEGRATION_PLUGIN QXcbIntegrationPlugin)
elseif(WIN32)
    set(INTEGRATION_PLUGIN QWindowsIntegrationPlugin)
else()
    message(FATAL_ERROR "Not supported OS")
endif()

find_package(Qt6 COMPONENTS Core Widgets Network ${INTEGRATION_PLUGIN} REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::${INTEGRATION_PLUGIN} Qt6::Core Qt6::Widgets Qt6::Network)
