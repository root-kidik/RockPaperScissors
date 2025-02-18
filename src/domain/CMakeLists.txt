set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC
    ${SRCROOT}/entity/Uuid.hpp
    ${SRCROOT}/entity/User.hpp

    ${SRCROOT}/handler/request/NewPlayerAdded.hpp
    ${SRCROOT}/handler/request/NewPlayerAdded.cpp
    ${SRCROOT}/handler/request/CardForcedNominated.hpp
    ${SRCROOT}/handler/request/CardForcedNominated.cpp
    ${SRCROOT}/handler/request/GameStarted.hpp
    ${SRCROOT}/handler/request/GameStarted.cpp
    ${SRCROOT}/handler/request/CardRaised.hpp
    ${SRCROOT}/handler/request/CardRaised.cpp
    ${SRCROOT}/handler/request/RoundInfo.hpp
    ${SRCROOT}/handler/request/RoundInfo.cpp

    ${SRCROOT}/handler/response/Register.hpp
    ${SRCROOT}/handler/response/Register.cpp
    ${SRCROOT}/handler/response/CreateRoom.hpp
    ${SRCROOT}/handler/response/CreateRoom.cpp
    ${SRCROOT}/handler/response/ConnectToRoom.hpp
    ${SRCROOT}/handler/response/ConnectToRoom.cpp
    ${SRCROOT}/handler/response/StartGame.hpp
    ${SRCROOT}/handler/response/StartGame.cpp

    ${SRCROOT}/model/Room.hpp
    ${SRCROOT}/model/Room.cpp
    ${SRCROOT}/model/HandOfCards.hpp
    ${SRCROOT}/model/HandOfCards.cpp

    ${SRCROOT}/usecase/Registration.hpp
    ${SRCROOT}/usecase/Registration.cpp
    ${SRCROOT}/usecase/Searching.hpp
    ${SRCROOT}/usecase/Searching.cpp
    ${SRCROOT}/usecase/StartGame.hpp
    ${SRCROOT}/usecase/StartGame.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PUBLIC RockPaperScissorsProtocol::RockPaperScissorsProtocol)
