#pragma once

#include "trength/graphics/window.hpp"
#include "trength/graphics/context.hpp"

namespace Trength::OpenGL {
	class Context : public Graphics::Context {
		public:
			Context(Graphics::Window& window);
			Context(const Context& other) = delete;
			virtual ~Context();
	};
};
