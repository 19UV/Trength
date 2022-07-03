# Trength

Trength is a hobby 4D game engine inspired by the game [Miegakure](https://miegakure.com/),
I'm not currently making a game with it, but who knows!

Currently, this project is being developed using MSC++ and CMake, although it doesn't directly
make any OS-specific syscalls, so it should be easy to port to Mac/Linux (this will be done
once the engine reaches a usable state).

## Usage
### Adding as a CMake Submodule
```console
> cd extern
> git submodule add https://github.com/19UV/Trength.git

> # Use add_submodule(extern/Trength) and target_link_libraries(<PROJECT> trength)
> # Also be sure to have the C++ standard at or above C++17

> cmake -B build/
> cmake --build build/
> # Run the resulting executable
```

### Building the Library
```console
> cmake -B build/
> cmake --build build/
> # The resulting files will be somewhere in build
```

## Roadmap
- [ ] Renderer
	- [ ] OpenGL
	- [ ] Vulkan
- [ ] Entity Component System (entt)
- [ ] 4D Mesh -> 3D Mesh

	...

- [ ] Physics
	Marc Ten Bosch - [N-Dimensional Rigid Body Dynamics](https://marctenbosch.com/ndphysics/NDrigidbody.pdf)

	...

- [ ] Support Other Platforms
	- [ ] Full Support of Linux
	- [ ] Full Support of OSX

	- [ ] Full Support of Clang
	- [ ] Full Support of GCC
- [ ] Implement other Graphics Backends (currently OpenGL and Vulkan)
	- [ ] Metal
	- [ ] Vulkan
