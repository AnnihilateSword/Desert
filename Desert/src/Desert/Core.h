#pragma once

#ifdef DESERT_PLATFORM_WINDOWS

#if DESERT_DYNAMIC_LINK
	#ifdef DESERT_BUILD_DLL
		#define DESERT_API __declspec(dllexport)
	#else
		#define DESERT_API __declspec(dllimport)
	#endif
#else
	#define DESERT_API
#endif

#else
	#error Desert only supports windows!

#endif

#ifdef DESERT_DEBUG
	#define DESERT_ENABLE_ASSERTS
#endif

#ifdef DESERT_ENABLE_ASSERTS

	#define DT_ASSERT(x, ...) { if(!(x)) { DT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DT_CORE_ASSERT(x, ...) { if(!(x)) { DT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

	#define DT_ASSERT(x, ...)
	#define DT_CORE_ASSERT(x, ...)

#endif

#define BIT(x) (1 << x)


#define DT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)