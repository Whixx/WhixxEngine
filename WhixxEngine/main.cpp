#include "stdafx.h"
#include "Renderer.h"
#include "Window.h"

void mainloop();

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)

{
    Window* window = Window::getInstance();
    // create the window
    if (!window->InitializeWindow(hInstance, nShowCmd))
    {
        MessageBox(0, L"Window Initialization - Failed",
            L"Error", MB_OK);
        return 1;
    }

    Renderer* renderer = Renderer::getInstance();
    // initialize direct3d
    if (!renderer->InitD3D())
    {
        MessageBox(0, L"Failed to initialize direct3d 12",
            L"Error", MB_OK);
        renderer->Cleanup();
        return 1;
    }

    // start the main loop
    mainloop();

    // we want to wait for the gpu to finish executing the command list before we start releasing everything
    renderer->WaitForPreviousFrame();


    // clean up everything
    renderer->Cleanup();

    return 0;
}


void mainloop() {
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (Running)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // run game code
            Renderer* renderer = Renderer::getInstance();
            renderer->Update(); // update the game logic
            renderer->Render(); // execute the command queue (rendering the scene is the result of the gpu executing the command lists)
        }
    }
}
