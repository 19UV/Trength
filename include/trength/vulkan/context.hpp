#pragma once

// I don't like polluting the global namespace, but this is needed
#include <vulkan/vulkan.h>

#include "trength/graphics/window.hpp"
#include "trength/graphics/context.hpp"

namespace Trength::Vulkan {
	class Context : public Graphics::Context {
		public:
			Context(Graphics::Window& window);
			Context(const Context& other) = delete;
			virtual ~Context();

		private:
			void create_instance();

			VkInstance instance;
	};
};
