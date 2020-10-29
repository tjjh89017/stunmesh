cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(stunmesh C)

set(CMAKE_C_STANDARD 99)

set(sources
	stunmesh
	linux_stun
)

set(STUNMESH stunmesh)

add_executable(${STUNMESH}
	$(sources)
)

target_include_directories($STUNMESH) PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
}

install(TARGETS ${EZIO}
	RUNTIME DESTINATION bin)
