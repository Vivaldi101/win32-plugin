#include <windows.h>
#include <iostream>

typedef void (*StartPluginWindowFunc)();
typedef void (*StopPluginWindowFunc)();

int main() {
    HMODULE plugin = LoadLibraryA("plugin.dll");
    if (!plugin) {
        std::cerr << "Failed to load plugin.dll!" << std::endl;
        return 1;
    }

    StartPluginWindowFunc StartPluginWindow = (StartPluginWindowFunc)GetProcAddress(plugin, "StartPluginWindow");
    StopPluginWindowFunc StopPluginWindow = (StopPluginWindowFunc)GetProcAddress(plugin, "StopPluginWindow");

    if (!StartPluginWindow || !StopPluginWindow) {
        std::cerr << "Failed to get plugin functions!" << std::endl;
        FreeLibrary(plugin);
        return 1;
    }

    StartPluginWindow();

	 //std::cin.get();

    StopPluginWindow();

    FreeLibrary(plugin);
    return 0;
}
