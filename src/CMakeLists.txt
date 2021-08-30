set(FUTURE_HPP_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
    Actor.cpp
    Application.cpp
    Command.cpp
    CommandQueue.cpp
    DataTables.cpp
    Entity.cpp
    Future.cpp
    Player.cpp
    Room.cpp
    SceneNode.cpp
    SpriteNode.cpp
    TextNode.cpp
    TriggerNode.cpp
    Utils.cpp
    gui/Button.cpp
    gui/Component.cpp
    gui/Container.cpp
    gui/Label.cpp
    states/GameOverState.cpp
    states/GameState.cpp
    states/MenuState.cpp
    states/PauseState.cpp
    states/SettingsState.cpp
    states/State.cpp
    states/StateStack.cpp
    states/TitleState.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${FUTURE_HPP_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
    )

else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics-d
        sfml-window-d
        sfml-system-d
    )
endif()