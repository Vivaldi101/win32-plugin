#include <windows.h>
#include <thread>
#include <atomic>

const char CLASS_NAME[] = "SimplePluginWindowClass";

static HWND hwnd = nullptr;
static HINSTANCE hInst = nullptr;
//static std::thread guiThread;
// export this for threading
static std::atomic<bool> running(false);

// Forward declarations
LRESULT CALLBACK PluginWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Thread function for GUI
void GuiThreadFunc(HINSTANCE hInstance) {
    // Register window class
    WNDCLASSEXA wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = PluginWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = CLASS_NAME;
    RegisterClassExA(&wc);

    hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "Plugin GUI Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        running = false;
        return; // Failed to create window
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (running && GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    hwnd = nullptr;
}

// Exported function to start GUI window & message loop
extern "C" __declspec(dllexport) void StartPluginWindow() {
    if (running) 
       return; // Already running
    running = true;
    hInst = (HINSTANCE)GetModuleHandle(NULL);
    //guiThread = std::thread(GuiThreadFunc, hInst);
	 GuiThreadFunc(hInst);
}

// Exported function to stop GUI window and message loop
extern "C" __declspec(dllexport) void StopPluginWindow() {
    if (!running) 
       return;
    running = false;

    //if (guiThread.joinable()) {
        //guiThread.join();
    //}
}

// Window procedure
LRESULT CALLBACK PluginWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
		 case WM_SIZE:
			 // When resized, invalidate the window so it repaints
			 InvalidateRect(hwnd, nullptr, TRUE);
			 break;
	 case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);

        // Fill background
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        // Draw something trivial - e.g. text centered
        const char* text = "Hello from Plugin Window.";
        SetBkMode(hdc, TRANSPARENT);
        DrawTextA(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        EndPaint(hwnd, &ps);
        break;
    }  
	 case WM_ERASEBKGND:
        // Return 1 to indicate we handled background erase to reduce flicker
        return 1;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
