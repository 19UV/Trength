#include "trength/graphics/window.hpp"

#include <stdexcept>

#include "trength/graphics/backends.hpp"

#include "trength/graphics/context.hpp"

#ifdef TRENGTH_BACKEND_OPENGL
#include "trength/opengl/context.hpp"
#else
#define GLFW_INCLUDE_NONE
#endif // TRENGTH_BACKEND_OPENGL

#ifdef TRENGTH_BACKEND_VULKAN
#include "trength/vulkan/context.hpp"
#define GLFW_INCLUDE_VULKAN
#endif // TRENGTH_BACKEND_VULKAN

#include <glfw/glfw3.h>

namespace Trength::Graphics {
	static unsigned int _window_count = 0;

	Window::Window(std::string& title, unsigned int width, unsigned int height)
		: Window(title.c_str(), width, height) {}

	Window::Window(const char* title, unsigned int width, unsigned int height) {
		auto backend = Backend::Vulkan;
		// auto backend = TRENGTH_BACKEND_DEFAULT;

		if((_window_count++) == 0 && !glfwInit()) {
			throw std::runtime_error("Could Not Create Window; Failed to initialize GLFW");
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		IFN_OPENGL(backend, glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API))

		this->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if(this->handle == nullptr) {
			throw std::runtime_error("Could Not Create Window; Failed to create window");
		}

		switch(backend) {
#ifdef TRENGTH_BACKEND_OPENGL
		case Backend::OpenGL:
			this->context = new OpenGL::Context(*this);
			break;
#endif
#ifdef TRENGTH_BACKEND_VULKAN
		case Backend::Vulkan:
			this->context = new Vulkan::Context(*this);
			break;
#endif
		}

		// FIXME: Add OpenGL
		// FIXME: Add Vulkan/Metal/Direct 3D
	}

	Window::~Window() {
		if(this->context != nullptr) {
			delete this->context;
		}

		if(this->handle != nullptr) {
			glfwDestroyWindow(this->handle);
		}

		if((--_window_count) == 0) {
			glfwTerminate();
		}
	}

	bool Window::should_close() {
		glfwPollEvents(); // May not want this

		return glfwWindowShouldClose(this->handle);
	}

	GLFWwindow* Window::get_handle() const {
		return this->handle;
	}
};
