#pragma once

#include "trength/graphics/window.hpp"

namespace Trength::Graphics {
	class Context {
		public:
			Context(Window& window);
			Context(const Context& other) = delete;
			virtual ~Context();

		private:
			Window& parent;
	};
};
