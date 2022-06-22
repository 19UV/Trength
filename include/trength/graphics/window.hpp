#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace Trength::Graphics {
	class Context;

	class Window {
		public:
			Window(const char* title, unsigned int width, unsigned int height);
			Window(std::string& title, unsigned int width, unsigned int height);
			Window(const Window& other) = delete;
			~Window();

			bool should_close();

		protected:
			friend class Context;

			GLFWwindow* get_handle() const;

			std::unique_ptr<Context> context;
		
		private:
			GLFWwindow* handle = nullptr;
	};
};
