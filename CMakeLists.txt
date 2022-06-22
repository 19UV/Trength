cmake_minimum_required(VERSION 3.11)

project(trength
	VERSION 0.1
	DESCRIPTION "A 4D Rendering Library"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

######################## 
# Dependency Locations # 
######################## 

set(EXTERN_GLFW extern/glfw)

###################### 
# Build Dependencies # 
###################### 

# Build GLFW 
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXTERN_GLFW})
set(TRENGTH_DEPEND ${TRENGTH_DEPEND} glfw)

################# 
# Build Trength # 
################# 

set(TRENGTH_SOURCE ${TRENGTH_SOURCE}
	src/graphics/context.cpp
	src/graphics/window.cpp
)

add_library(trength ${TRENGTH_SOURCE})
target_include_directories(trength PUBLIC include/)
target_link_libraries(trength PUBLIC ${TRENGTH_DEPEND})
