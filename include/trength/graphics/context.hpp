#pragma once

#include "trength/graphics/window.hpp"
#include "trength/graphics/backends.hpp"

struct GLFWwindow;

namespace Trength::Graphics {
	class Context {
		public:
			Context(Window& window);
			Context(const Context& other) = delete;
			virtual ~Context();

			virtual Backend backend() const;

			void make_current();

			static const Context* current();

		protected:
			Window& get_window() const;
			GLFWwindow* get_handle() const;

		private:
			Window& parent;
	};
};
