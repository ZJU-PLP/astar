project(main)

find_package(PkgConfig)
pkg_check_modules(SDL sdl)
pkg_check_modules(SDLIMAGE SDL_image)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${SDL_INCLUDE_DIRS})

add_executable(main
	main.cpp
)

target_link_libraries(main ${SDL_LIBRARIES} ${SDLIMAGE_LIBRARIES} boost_filesystem boost_system)
