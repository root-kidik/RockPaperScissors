add_executable(${PROJECT_NAME} Main.cpp)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Network)
target_include_directories(${PROJECT_NAME} PRIVATE ${Qt6_INCLUDE_DIRS})