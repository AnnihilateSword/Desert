#pragma once

#ifdef DESERT_PLATFORM_WINDOWS

	#ifdef DESERT_BUILD_DLL
		#define DESERT_API __declspec(dllexport)
	#else
		#define DESERT_API __declspec(dllimport)
	#endif

#else
	#error Desert only supports windows!

#endif

#ifdef DESERT_ENABLE_ASSERTS

	#define DESERT_ASSERT(x, ...) { if(!(x)) { DESERT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DESERT_CORE_ASSERT(x, ...) { if(!(x)) { DESERT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

	#define DESERT_ASSERT(x, ...)
	#define DESERT_CORE_ASSERT(x, ...)

#endif

#define BIT(x) (1 << x)