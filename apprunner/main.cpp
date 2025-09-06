#include <windows.h>
#include <cstdio>

typedef void (*StartPluginWindowFunc)();
typedef void (*StopPluginWindowFunc)();

int main()
{
    HMODULE plugin = LoadLibraryA("plugin.dll");
    if (!plugin)
    {
        printf("Failed to load plugin.dll!");
        return 1;
    }

    StartPluginWindowFunc StartPluginWindow = (StartPluginWindowFunc)GetProcAddress(plugin, "StartPluginWindow");
    StopPluginWindowFunc StopPluginWindow = (StopPluginWindowFunc)GetProcAddress(plugin, "StopPluginWindow");

    if (!StartPluginWindow || !StopPluginWindow)
    {
        printf("Failed to get plugin functions!");
        FreeLibrary(plugin);
        return 1;
    }

    StartPluginWindow();
	 StopPluginWindow();

    FreeLibrary(plugin);
    return 0;
}
