#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>

#include "win32_gefs.h"

static void
Win32InitOpenGL(HWND Window)
{
    HDC WindowDC = GetDC(Window);

    PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
    DesiredPixelFormat.nSize = sizeof(DesiredPixelFormat);
    DesiredPixelFormat.nVersion = 1;
    DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
    DesiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW|PFD_DOUBLEBUFFER;
    DesiredPixelFormat.cColorBits = 32;
    DesiredPixelFormat.cAlphaBits = 8;
    DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

    int SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);
    PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
    DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
    SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);

    HGLRC OpenGLRC = wglCreateContext(WindowDC);
    if(wglMakeCurrent(WindowDC, OpenGLRC))
    {

    }
    else
    {

    }

    ReleaseDC(Window, WindowDC);
}

static win32_window_dimension
Win32GetWindowDimension(HWND Window)
{
    win32_window_dimension Result;
    
    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Result.Width = ClientRect.right - ClientRect.left;
    Result.Height = ClientRect.bottom - ClientRect.top;

    return(Result);
}

static void
Win32DisplayBufferInWindow(HDC DeviceContext, int WindowWidth, int WindowHeight)
{
    glViewport(0, 0, WindowWidth, WindowHeight);

    // GLuint TextureHandle;
    // static bool Init = false;
    // if(!Init)
    // {
    //     glGenTextures(1, &TextureHandle);
    //     Init = true;
    // }

    // glBindTexture(GL_TEXTURE_2D, TextureHandle);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Buffer->Width, Buffer->Height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Buffer->Memory);

    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glEnd();

    SwapBuffers(DeviceContext);
}

static LRESULT CALLBACK
Win32MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{       
    switch(Message)
    {
        case WM_CLOSE:
        {
            DestroyWindow(Window);
        } break;
        case WM_DESTROY: 
        {
            PostQuitMessage(0);
        } break;
        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC DeviceContext = BeginPaint(Window, &paint);
            win32_window_dimension Dimension = Win32GetWindowDimension(Window);
            Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height);
            EndPaint(Window, &paint);
        } break;
        default:
        {
            return DefWindowProc(Window, Message, WParam, LParam);
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX WindowClass;
    HWND hwnd;
    MSG Msg;

    WindowClass.cbSize        = sizeof(WNDCLASSEX);
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = Win32MainWindowCallback;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = hInstance;
    WindowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    WindowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    WindowClass.lpszMenuName  = NULL;
    WindowClass.lpszClassName = "GEFSWindoWindowClasslass";
    WindowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&WindowClass))
    {
        printf("Window Registration Failed!");
        return 0;
    }

    HWND Window  = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        WindowClass.lpszClassName,
        "GEFS",
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL);

    if(Window == NULL)
    {
        printf("Window Creation Failed!");
        return 0;
    }

    Win32InitOpenGL(Window);
    ShowWindow(Window, nCmdShow);
    UpdateWindow(Window);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}