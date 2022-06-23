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
set(EXTERN_GLAD extern/glad)

###################### 
# Build Dependencies # 
###################### 

# Build GLFW 
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXTERN_GLFW})
set(TRENGTH_DEPEND ${TRENGTH_DEPEND} glfw)

# Find (and build) OpenGL/GLAD 
find_package(OpenGL)
if(OPENGL_FOUND)
	set(TRENGTH_SOURCE ${TRENGTH_SOURCE}
		src/opengl/context.cpp
	)

	add_subdirectory(${EXTERN_GLAD})

	set(TRENGTH_DEPEND ${TRENGTH_DEPEND} OpenGL::GL glad)
	set(TRENGTH_DEFINE ${TRENGTH_DEFINE} TRENGTH_BACKEND_OPENGL)
endif()

find_package(Vulkan)
if(Vulkan_FOUND)
	set(TRENGTH_DEPEND ${TRENGTH_DEPEND} Vulkan::Vulkan)
	set(TRENGTH_DEFINE ${TRENGTH_DEFINE} TRENGTH_BACKEND_VULKAN)
endif()

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
target_compile_definitions(trength PRIVATE ${TRENGTH_DEFINE})
