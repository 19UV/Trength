#pragma once

namespace Trength::Graphics {
	enum Backend {
#ifdef TRENGTH_BACKEND_OPENGL
		OpenGL,
#endif // TRENGTH_BACKEND_OPENGL

#ifdef TRENGTH_BACKEND_VULKAN
		Vulkan,
#endif // TRENGTH_BACKEND_VULKAN
	};
};

// Find the best graphics backend, will be in order (Direct3D | Metal), Vulkan, OpenGL
#if defined(TRENGTH_BACKEND_VULKAN)
#	define TRENGTH_BACKEND_DEFAULT Trength::Graphics::Backend::OpenGL
#elif defined(TRENGTH_BACKEND_OPENGL)
#	define TRENGTH_BACKEND_DEFAULT Trength::Graphics::Backend::Vulkan
#else
#	error A backend must be defined
#endif

// Detecting OpenGL
#ifdef TRENGTH_BACKEND_OPENGL
#	define IF_OPENGL(e, code) if(e == Trength::Graphics::Backend::OpenGL) code;
#	define IFN_OPENGL(e, code) if(e != Trength::Graphics::Backend::OpenGL) code;
#else
#	define IF_OPENGL(e, code)
#	define IFN_OPENGL(e, code)
#endif

// Detecting Vulkan
#ifdef TRENGTH_BACKEND_VULKAN
#	define IF_VULKAN(e, code) if(e == Trength::Graphics::Backend::Vulkan) code;
#	define IFN_VULKAN(e, code) if(e != Trength::Graphics::Backend::Vulkan) code;
#else
#	define IF_VULKAN(e, code)
#	define IFN_VULKAN(e, code)
#endif
