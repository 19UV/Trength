#pragma once

#include "trength/graphics/window.hpp"

struct GLFWwindow;

namespace Trength::Graphics {
	class Context {
		public:
			Context(Window& window);
			Context(const Context& other) = delete;
			virtual ~Context();

		protected:
			Window& get_window() const;
			GLFWwindow* get_handle() const;

		private:
			Window& parent;
	};
};
