#include "trength/graphics/window.hpp"

#include <stdexcept>

#include <glfw/glfw3.h>

#include "trength/graphics/context.hpp"

#ifdef TRENGTH_BACKEND_OPENGL
#include "trength/opengl/context.hpp"
#endif // TRENGTH_BACKEND_OPENGL

namespace Trength::Graphics {
	static unsigned int _window_count = 0;

	Window::Window(std::string& title, unsigned int width, unsigned int height)
		: Window(title.c_str(), width, height) {}

	Window::Window(const char* title, unsigned int width, unsigned int height) {
		if((_window_count++) == 0 && !glfwInit()) {
			throw std::runtime_error("Could Not Create Window; Failed to initialize GLFW");
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		this->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if(this->handle == nullptr) {
			throw std::runtime_error("Could Not Create Window; Failed to create window");
		}

		this->context = std::make_unique<OpenGL::Context>(*this);

		// FIXME: Add OpenGL
		// FIXME: Add Vulkan/Metal/Direct 3D
	}

	Window::~Window() {
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
