add_executable(${PROJECT_NAME}
    Future.cpp
)

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