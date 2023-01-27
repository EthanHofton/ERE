#include <ereConfig.hpp>

#ifdef _WIN32
    #ifdef _WIN64
        #define ERE_PLATFORM_WINDOWS
        #error "Windows not supported"
    #else
        #define ERE_PLATFORM_WINDOWS
        #error "Windows not supported"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
        #define ERE_PLATFORM_IOS_SIMULATOR
		#error "IOS simulator not supported"
	#elif TARGET_OS_IPHONE == 1
		#define ERE_PLATFORM_IOS
        #error "IOS not supported"
	#elif TARGET_OS_MAC == 1
		#define ERE_PLATFORM_OSX
	#else
		#error "Unknown Apple platform"
	#endif
#elif defined(__ANDROID__)
    #define ERE_PLATFORM_ANDRIOID
    #error "Andrioid not supported"
#elif defined(__linux__)
    #define DM3_PLATFORM_LINUX
    #error "Linux not supported"
#else
    #error "Unknown platform"
#endif
