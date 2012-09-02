project(tests)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(
    tests
    astarwalker.cpp
    main.cpp
    matrix.cpp
    MapReaderTest.cpp
)

target_link_libraries(tests rtest boost_filesystem boost_system)
