set(TARGET_SUFFIX infrastructure)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/RockPaperScissors.hpp
    ${SRCROOT}/RockPaperScissors.cpp

    ${SRCROOT}/client/TcpSocketConnection.hpp
    ${SRCROOT}/client/TcpSocketConnection.cpp

    ${SRCROOT}/storage/Pixmap.hpp
    ${SRCROOT}/storage/Pixmap.cpp

    ${SRCROOT}/widget/HandOfCards.hpp
    ${SRCROOT}/widget/HandOfCards.cpp
    ${SRCROOT}/widget/Manager.hpp
    ${SRCROOT}/widget/MainMenu.hpp
    ${SRCROOT}/widget/MainMenu.cpp
    ${SRCROOT}/widget/Registration.hpp
    ${SRCROOT}/widget/Registration.cpp
    ${SRCROOT}/widget/Searching.hpp
    ${SRCROOT}/widget/Searching.cpp
    ${SRCROOT}/widget/Room.hpp
    ${SRCROOT}/widget/Room.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

if(UNIX AND NOT APPLE)
    set(INTEGRATION_PLUGIN QXcbIntegrationPlugin)
elseif(WIN32)
    set(INTEGRATION_PLUGIN QWindowsIntegrationPlugin)
else()
    message(FATAL_ERROR "Not supported OS")
endif()

find_package(Qt6 COMPONENTS ${INTEGRATION_PLUGIN} Core Widgets Network REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC Qt6::${INTEGRATION_PLUGIN} Qt6::Core Qt6::Widgets Qt6::Network ${PROJECT_NAME}::domain)

qt_add_resources(${TARGET_NAME} "assets"
    FILES ../../assets/Rock.png ../../assets/Paper.png ../../assets/Scissors.png ../../assets/Backface.png
)
