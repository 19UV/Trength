#include "trength/opengl/context.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Trength::OpenGL {
	Context::Context(Graphics::Window& window) : Graphics::Context(window) {
		glfwMakeContextCurrent(this->get_handle());

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Could Not Create OpenGL Context; Failed to initialize GLAD");
		}
	}

	Context::~Context() {
	}
};
