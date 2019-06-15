#include "RkPlatform.h"
#include "RkEventQueue.h"
#include "RkEvent.h"

#include <random>

static std::string rk_winApiClassName;
static HINSTANCE rk_winApiInstance = nullptr;
#ifdef RK_GRAPHICS_BACKEND_DIRECT2D
#include <d2d1.h>
static ID2D1Factory* rk_d2d1Factory = nullptr;
#endif // RK_GRAPHICS_BACKEND_DIRECT2D

HINSTANCE rk_win_api_instance()
{
        return rk_winApiInstance;
}

std::string rk_win_api_class_name()
{
        return rk_winApiClassName;
}

RkNativeWindowInfo rk_from_native_win(HWND window, HINSTANCE instance = nullptr, LPCSTR className = nullptr)
{
        RkNativeWindowInfo info;
        info.instance = instance ? instance : rk_winApiInstance;
        info.className = className ? className : rk_winApiClassName;
        info.window = window;
        return info;
}

RkWindowId rk_id_from_win(HWND window)
{
        RkWindowId id;
        id.id = window;
        return id;
}

#ifdef RK_GRAPHICS_BACKEND_DIRECT2D
ID2D1Factory* RK_EXPORT rk_direct2d_factory()
{
        return rk_d2d1Factory;
}
#endif // RK_GRAPHICS_BACKEND_DIRECT2D

static LRESULT CALLBACK RkWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        auto eventQueue = (RkEventQueue*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (!eventQueue)
                return DefWindowProc(hWnd, msg, wParam, lParam);

        switch(msg)
        {
        case WM_DESTROY:
        {
                //auto event = RkEvent::closeEvent();
                //eventQueue->processEvent(rk_id_from_win(hWnd), event);
                return 0;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
		{
                //auto event = RkMouseEvent
                //eventQueue->processEvent(rk_id_from_win(hWnd), event);
                return 0;
		}
        case WM_PAINT:
        {
                //auto event = RkEvent::paintEvent();
                //eventQueue->processEvent(rk_id_from_win(hWnd), event);
                break;
        }
        default:
                break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
}

#ifdef RK_FOR_SHARED
BOOL WINAPI DllMain(HINSTANCE hInstance,
                    DWORD fdwReason,
                    LPVOID lpvReserved)
{
        rk_winApiInstance = hInstance;
		RK_LOG_DEBUG("instance:" << rk_winApiInstance);
        WNDCLASSEX wc;
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = RkWindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName  = NULL;

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 1000000);
        int mean = uniform_dist(e1);
        rk_winApiClassName = ("Redkite_" + std::to_string(mean)).c_str();
        wc.lpszClassName = rk_winApiClassName.c_str();
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

#ifdef RK_GRAPHICS_BACKEND_DIRECT2D
        if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &rk_d2d1Factory) != S_OK) {
                RK_LOG_ERROR("can't create D2D1 factory");
                return FALSE;
        }
#endif // RK_GRAPHICS_BACKEND_DIRECT2D

        if (!RegisterClassEx(&wc)) {
                RK_LOG_ERROR("can't register window class");
                return FALSE;
        }

        return TRUE;
}
#else // RK_FOR_SHARED
static inline char *wideToMulti(int codePage, const wchar_t *aw)
{
        const int required = WideCharToMultiByte(codePage, 0, aw, -1, NULL, 0, NULL, NULL);
        char *result = new char[required];
        WideCharToMultiByte(codePage, 0, aw, -1, result, required, NULL, NULL);
        return result;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
        rk_winApiInstance = hInstance;
		RK_LOG_DEBUG("instance:" << rk_winApiInstance);
        WNDCLASSEX wc;
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = RkWindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName  = NULL;

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 1000000);
        int mean = uniform_dist(e1);
        rk_winApiClassName = "Redkite_" + std::to_string(mean);
        wc.lpszClassName = rk_winApiClassName.c_str();
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
		
		
#ifdef RK_GRAPHICS_BACKEND_DIRECT2D
        if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &rk_d2d1Factory) != S_OK) {
                RK_LOG_ERROR("can't create D2D1 factory");
                return FALSE;
        }
#endif // RK_GRAPHICS_BACKEND_DIRECT2D

        if (!RegisterClassEx(&wc)) {
                RK_LOG_ERROR("can't register window class");
                return 1;
        }

        int argc;
        wchar_t **argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
        if (!argvW)
                return 1;

        std::vector<char*> args(argc, nullptr);
        for (decltype(args.size()) i = 0; i < args.size(); i++)
                args[i] = wideToMulti(CP_ACP, argvW[i]);
        LocalFree(argvW);

        const int exitCode = main(args.size(), args.data());
        for (auto arg : args)
                delete [] arg;

        return exitCode;
}
#endif // RK_FOR_SHARED
