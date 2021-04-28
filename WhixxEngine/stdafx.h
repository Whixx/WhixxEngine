#ifndef STDAFX_H
#define STDAFX_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <string>

// this will only call release if an object exists (prevents exceptions calling release on non existant objects)
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

// Handle to the window
static HWND hwnd = NULL;

// name of the window (not the title)
static LPCTSTR WindowName = L"WhixxEngine";

// title of the window
static LPCTSTR WindowTitle = L"WhixxEngine";

// width and height of the window
static int WindowWidth = 800;
static int WindowHeight = 600;

// is window full screen?
static bool FullScreen = false;

// we will exit the program when this becomes false
static bool Running = true;

// function declarations

// create a window
bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool fullscreen);

// main application loop
void mainloop();

// callback function for windows messages
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);



// Direct3D declarations

// Render Targets : Number of frame buffers
// Command Allocators : Number of frame buffers* number of threads
// Fences : Number of threads
// Fence Values : Number of threads
// Fence Events : Number of threads
// Command Lists : Number of threads

static const int frameBufferCount = 3; // number of buffers we want, 2 for double buffering, 3 for tripple buffering

static ID3D12Device* device; // Direct3D device

static IDXGISwapChain3* swapChain; // swapchain used to switch between render targets

static ID3D12CommandQueue* commandQueue; // container for command lists

static ID3D12DescriptorHeap* rtvDescriptorHeap; // a descriptor heap to hold resources like the render targets

static ID3D12Resource* renderTargets[frameBufferCount]; // number of render targets equal to buffer count

static ID3D12CommandAllocator* commandAllocator[frameBufferCount]; // we want enough allocators for each buffer * number of threads (we only have one thread)

static ID3D12GraphicsCommandList* commandList; // a command list we can record commands into, then execute them to render the frame

static ID3D12Fence* fence[frameBufferCount]; // an object that is locked while our command list is being executed by the gpu. We need as many 
											 // as we have allocators (more if we want to know when the gpu is finished with an asset)

static HANDLE fenceEvent; // a handle to an event when our fence is unlocked by the gpu

static UINT64 fenceValue[frameBufferCount]; // this value is incremented each frame. each fence will have its own value

static int frameIndex; // current rtv we are on

static int rtvDescriptorSize; // size of the rtv descriptor on the device (all front and back buffers will be the same size)

// function declarations
bool InitD3D(); // initializes Direct3D 12

void Update(); // update the game logic

void UpdatePipeline(); // update the Direct3D pipeline (update command lists)

void Render(); // execute the command list

void Cleanup(); // release com ojects and clean up memory

void WaitForPreviousFrame(); // wait until gpu is finished with command list




#endif // STDAFX_H