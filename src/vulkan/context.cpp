#include "trength/vulkan/context.hpp"

#include <iostream>
#include <vector>
#include <optional>
#include <stdexcept>
#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "trength/info.hpp"

namespace Trength::Vulkan {
	Context::Context(Graphics::Window& window) : Graphics::Context(window) {
		this->create_instance();
		// TODO: Implement Validation Layers for Debugging
		
		VkPhysicalDevice physical_device = this->pick_physical_device();
		this->create_logical_device(physical_device);

		this->get_queue_handles(physical_device);
	}

	Context::~Context() {
		vkDestroyDevice(this->device, nullptr);

		vkDestroyInstance(this->instance, nullptr);
	}

	void Context::create_instance() {
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Trength Application"; // TODO: Get name from CMake config?
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // TODO: Get application version
		app_info.pEngineName = "Trength";
		app_info.engineVersion = VK_MAKE_VERSION(
			TRENGTH_VERSION_MAJOR,
			TRENGTH_VERSION_MINOR,
			TRENGTH_VERSION_PATCH
		);
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

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphics_family;

		QueueFamilyIndices(const VkPhysicalDevice& device) {
			uint32_t family_count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, nullptr);

			std::vector<VkQueueFamilyProperties> families(family_count);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, families.data());

			uint32_t i = 0;
			for(const auto& family : families) {
				if(family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
					this->graphics_family = i;

					break;
				}

				i++;
			}
		}

		bool complete() {
			return this->graphics_family.has_value();
		}
	};

	static bool device_suitable(const VkPhysicalDevice& device) {
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;

		vkGetPhysicalDeviceProperties(device, &properties);
		vkGetPhysicalDeviceFeatures(device, &features);

		QueueFamilyIndices indices(device);

		std::cerr << "Device Name: " << properties.deviceName << std::endl;

		return indices.complete();
	}


	VkPhysicalDevice Context::pick_physical_device() {
		VkPhysicalDevice physical_device = VK_NULL_HANDLE;

		uint32_t device_count = 0;
		vkEnumeratePhysicalDevices(this->instance, &device_count, nullptr);
		if(device_count == 0) {
			throw std::runtime_error("Failed to Find GPUs with Vulkan Support");
		}

		std::vector<VkPhysicalDevice> devices(device_count);
		vkEnumeratePhysicalDevices(this->instance, &device_count, devices.data());

		// TODO: Implement a scoring system for devices
		// store in a multimap
		for(const VkPhysicalDevice& device : devices) {
			if(device_suitable(device)) {
				physical_device = device;
				break;
			}
		}

		if(physical_device == VK_NULL_HANDLE) {
			throw std::runtime_error("Failed to Find a Suitable GPU");
		}

		return physical_device;
	}

	void Context::create_logical_device(const VkPhysicalDevice& physical_device) {
		QueueFamilyIndices indices(physical_device);

		// TODO: If we want to use GPGPU stuff, I will need to create more queues
		// Or if I just want more Queues.

		float queue_priority = 1.0f;
		VkDeviceQueueCreateInfo queue_create_info{};
		queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueFamilyIndex = indices.graphics_family.value();
		queue_create_info.queueCount = 1;
		queue_create_info.pQueuePriorities = &queue_priority;

		VkPhysicalDeviceFeatures device_features{};

		VkDeviceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		create_info.pQueueCreateInfos = &queue_create_info;
		create_info.queueCreateInfoCount = 1;
		create_info.pEnabledFeatures = &device_features;

		create_info.enabledExtensionCount = 0; // TODO: Add more extensions (ex. Geometry Shaders)
		create_info.enabledLayerCount = 0; // TODO: Add more layers

		if(vkCreateDevice(physical_device, &create_info, nullptr, &this->device) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Create a Logical Device");
		}
	}

	void Context::get_queue_handles(const VkPhysicalDevice& physical_device) {
		QueueFamilyIndices indices(physical_device);

		vkGetDeviceQueue(this->device, indices.graphics_family.value(), 0, &this->graphics_queue);
	}
};
