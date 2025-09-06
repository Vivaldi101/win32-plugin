#pragma once

#ifdef _WIN32
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API
#endif

extern "C" {
    PLUGIN_API void RunPlugin();
}
