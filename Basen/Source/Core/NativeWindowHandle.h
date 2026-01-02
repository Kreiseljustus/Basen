#pragma once

#ifdef WINDOWS
#include <Windows.h>
#elif defined(LINUX)
#include <X11/Xlib.h>
#endif

namespace Basen {
	struct NativeWindowHandle {
#ifdef WINDOWS
		HWND hwnd;
#elif defined(LINUX)
		::Window x11Window;
		Display* display;
#endif

		void* GetPlatformHandle() const {
#ifdef WINDOWS
			return hwnd;
#elif defined(LINUX)
			return (void*)(uintptr_t)x11Window;
#endif
		}
	};
}