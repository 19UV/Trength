#include "trength/vulkan/context.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace Trength::Vulkan {
	Context::Context(Graphics::Window& window) : Graphics::Context(window) {
		this->create_instance();
	}

	Context::~Context() {
		vkDestroyInstance(this->instance, nullptr);
	}

	void Context::create_instance() {
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Trength Application"; // TODO: Get name from CMake config?
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // TODO: Get application version
		app_info.pEngineName = "Trength";
		app_info.engineVersion = VK_MAKE_VERSION(0, 0, 1); // TODO: Get Trength version
		app_info.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		glfwMakeContextCurrent(this->get_handle());

		// TODO: Add optional extensions (Geometry Shader)

		uint32_t extension_count = 0;
		const char** extensions = glfwGetRequiredInstanceExtensions(&extension_count);

		create_info.enabledExtensionCount = extension_count;
		create_info.ppEnabledExtensionNames = extensions;
		create_info.enabledLayerCount = 0; // TODO: Add more layers

		if(vkCreateInstance(&create_info, nullptr, &this->instance) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Create Vulkan Instance");
		}
	}
};
