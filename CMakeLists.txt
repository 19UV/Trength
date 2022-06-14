cmake_minimum_required(VERSION 3.11)

project(trength
	VERSION 0.1
	DESCRIPTION "A 4D Rendering Library"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(trength ${TRENGTH_SOURCE})
target_include_directories(trength PUBLIC include/)
target_link_libraries(trength PUBLIC ${TRENGTH_DEPEND})
