#pragma once

class Window
{
private:
	HWND hwnd;
	LPCTSTR WindowName = L"WhixxEngine";
	LPCTSTR WindowTitle = L"WhixxEngine";
	int Width = 800;
	int Height = 600;
	bool Fullscreen = false;

public:
	friend class Renderer;

	static Window* getInstance();
	bool InitializeWindow(HINSTANCE hInstance, int ShowWnd);
};

