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
			VkPhysicalDevice pick_physical_device();
			void create_logical_device(const VkPhysicalDevice& physical_device);
			void get_queue_handles(const VkPhysicalDevice& physical_device);

			VkInstance instance = VK_NULL_HANDLE;
			VkDevice device = VK_NULL_HANDLE;
			
			// May want to have an array or map?
			VkQueue graphics_queue = VK_NULL_HANDLE;
	};
};
