#include "trength/graphics/context.hpp"

#include <iostream>

namespace Trength::Graphics {
	Context::Context(Window& window) : parent(window) {
		GLFWwindow* handle = this->parent.get_handle();
	}

	Context::~Context() {
	}
};
