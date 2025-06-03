set(NAME main)

set(SOURCES
	main.c
)

add_executable(${NAME} ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(${NAME} PUBLIC Threads::Threads)

target_link_libraries(${NAME} PRIVATE mxml)
