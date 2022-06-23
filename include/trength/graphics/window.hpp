#pragma once

#include <string>

struct GLFWwindow;

#ifdef TRENGTH_BACKEND_OPENGL
namespace Trength::OpenGL { class Context; };
#endif // TRENGTH_BACKEND_OPENGL

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

			Context* context = nullptr;
		
		private:
			GLFWwindow* handle = nullptr;
	};
};
