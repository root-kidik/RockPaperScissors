set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC
    ${SRCROOT}/entity/Uuid.hpp
    ${SRCROOT}/entity/User.hpp

    ${SRCROOT}/handler/request/CardForced.hpp
    ${SRCROOT}/handler/request/CardForced.cpp
    ${SRCROOT}/handler/response/Register.hpp
    ${SRCROOT}/handler/response/Register.cpp
    ${SRCROOT}/handler/response/CreateRoom.hpp
    ${SRCROOT}/handler/response/CreateRoom.cpp
    ${SRCROOT}/handler/response/ConnectToRoom.hpp
    ${SRCROOT}/handler/response/ConnectToRoom.cpp

    ${SRCROOT}/model/Registration.hpp
    ${SRCROOT}/model/Registration.cpp
    ${SRCROOT}/model/RoomSearch.hpp
    ${SRCROOT}/model/RoomSearch.cpp
    ${SRCROOT}/model/RoomWait.hpp
    ${SRCROOT}/model/RoomWait.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PUBLIC RockPaperScissorsProtocol::RockPaperScissorsProtocol)
