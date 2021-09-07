set(FUTURE_HPP_DIR ${CMAKE_SOURCE_DIR}/src)

set(SOURCES
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

set(HEADERS
    Future/Actor.hpp
    Future/Application.hpp
    Future/Category.hpp
    Future/Command.hpp
    Future/CommandQueue.hpp
    Future/DataTables.hpp
    Future/Entity.hpp
    Future/Player.hpp
    Future/ResourceHolder.hpp
    Future/ResourceIdentifiers.hpp
    Future/Room.hpp
    Future/SceneNode.hpp
    Future/SpriteNode.hpp
    Future/TextNode.hpp
    Future/TriggerNode.hpp
    Future/Utils.hpp
    Future/json.hpp
    gui/Button.hpp
    gui/Component.hpp
    gui/Container.hpp
    gui/Label.hpp
    states/GameOverState.hpp
    states/GameState.hpp
    states/MenuState.hpp
    states/PauseState.hpp
    states/SettingsState.hpp
    states/State.hpp
    states/StateIdentifiers.hpp
    states/StateStack.hpp
    states/TitleState.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT_NAME} PRIVATE 
    -fsanitize=address
    -Wall 
    -Wextra 
    -Wshadow 
    -Wnon-virtual-dtor 
    -pedantic
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wuseless-cast
    -Wdouble-promotion
    -Wformat=2
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

target_link_options(${PROJECT_NAME} PRIVATE
    -fsanitize=address
)

endif()
