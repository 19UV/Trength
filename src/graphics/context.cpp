#include "trength/graphics/context.hpp"

#include <cassert>

static Trength::Graphics::Context* current_context = nullptr;

namespace Trength::Graphics {
	Context::Context(Window& window) : parent(window) {
	}

	Context::~Context() {
		if(current_context == this) {
			current_context = nullptr;
		}
	}

	Backend Context::backend() const {
		assert(false);
		return {};
	}

	Window& Context::get_window() const {
		return this->parent;
	}

	GLFWwindow* Context::get_handle() const {
		return this->parent.get_handle();
	}

	void Context::make_current() {
		current_context = this;
	}

	const Context* Context::current() {
		return current_context;
	}
};
