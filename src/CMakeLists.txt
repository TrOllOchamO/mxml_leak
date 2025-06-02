set(NAME main)

set(SOURCES
	main.c
)

add_executable(${NAME} ${SOURCES})
target_link_libraries(${NAME} PRIVATE mxml)
