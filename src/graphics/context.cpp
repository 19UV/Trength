#include "trength/graphics/context.hpp"

namespace Trength::Graphics {
	Context::Context(Window& window) : parent(window) {
	}

	Context::~Context() {
	}

	Window& Context::get_window() const {
		return this->parent;
	}

	GLFWwindow* Context::get_handle() const {
		return this->parent.get_handle();
	}
};
