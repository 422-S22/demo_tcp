add_executable(server
    main.cpp
    server.cpp
    server.h
)

target_link_libraries(server PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
)