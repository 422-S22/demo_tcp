add_executable(client
    main.cpp
    client.cpp
    client.h
)

target_link_libraries(client PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
)