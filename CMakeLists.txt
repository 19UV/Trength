cmake_minimum_required(VERSION 3.11)

# NOTE: To update versioning, update it in info.hpp
file(READ "include/trength/info.hpp" TRENGTH_INFO_FILE)
string(REGEX MATCH "#define[ ]+TRENGTH_VERSION_MAJOR[ ]+([0-9]+)" _ ${TRENGTH_INFO_FILE})
set(TRENGTH_VERSION_MAJOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+TRENGTH_VERSION_MINOR[ ]+([0-9]+)" _ ${TRENGTH_INFO_FILE})
set(TRENGTH_VERSION_MINOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+TRENGTH_VERSION_PATCH[ ]+([0-9]+)" _ ${TRENGTH_INFO_FILE})
set(TRENGTH_VERSION_PATCH "${CMAKE_MATCH_1}")

project(trength
	VERSION ${TRENGTH_VERSION_MAJOR}.${TRENGTH_VERSION_MINOR}.${TRENGTH_VERSION_PATCH}
	DESCRIPTION "A 4D Rendering Library"
	LANGUAGES CXX
)
message(STATUS "Trength Version: ${TRENGTH_VERSION_MAJOR}.${TRENGTH_VERSION_MINOR}.${TRENGTH_VERSION_PATCH}")

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
	message(STATUS "Found OpenGL")

	set(TRENGTH_SOURCE ${TRENGTH_SOURCE}
		src/opengl/context.cpp
	)

	add_subdirectory(${EXTERN_GLAD})

	set(TRENGTH_DEPEND ${TRENGTH_DEPEND} OpenGL::GL glad)
	set(TRENGTH_DEFINE ${TRENGTH_DEFINE} TRENGTH_BACKEND_OPENGL)
endif()

# Find Vulkan
find_package(Vulkan)
if(Vulkan_FOUND)
	message(STATUS "Found Vulkan")

	set(TRENGTH_SOURCE ${TRENGTH_SOURCE}
		src/vulkan/context.cpp
	)

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
