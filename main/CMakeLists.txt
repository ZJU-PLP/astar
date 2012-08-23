project(main)

find_package(PkgConfig)
pkg_check_modules(SDL sdl)
pkg_check_modules(SDLIMAGE SDL_image)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${SDL_INCLUDE_DIRS})

add_executable(main
	Background.cpp
	main.cpp
)

target_link_libraries(main ${SDL_LIBRARIES} sdl_image boost_filesystem boost_system)
