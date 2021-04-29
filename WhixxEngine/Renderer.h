#pragma once

#include "GPUstructs.h"


class Renderer
{
private:
	static const int frameBufferCount = 3;
	int frameIndex;

	ID3D12Device* device;
	IDXGISwapChain3* swapChain;
	ID3D12CommandQueue* commandQueue;
	ID3D12CommandAllocator* commandAllocator[frameBufferCount];
	ID3D12GraphicsCommandList* commandList;
	ID3D12PipelineState* pipelineStateObject;
	ID3D12RootSignature* rootSignature;

	ID3D12Fence* fence[frameBufferCount];
	HANDLE fenceEvent;
	UINT64 fenceValue[frameBufferCount];

	int rtvDescriptorSize;
	int cbPerObjectAlignedSize = (sizeof(ConstantBuffer) + 255) & ~255;

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	ID3D12DescriptorHeap* rtvDescriptorHeap;
	ID3D12DescriptorHeap* dsDescriptorHeap;
	ID3D12DescriptorHeap* mainDescriptorHeap[frameBufferCount]; // this heap will store the descripor to our constant buffer

	ID3D12Resource* constantBufferUploadHeap[frameBufferCount]; // this is the memory on the gpu where our constant buffer will be placed.
	ID3D12Resource* renderTargets[frameBufferCount];
	ID3D12Resource* vertexBuffer;
	ID3D12Resource* indexBuffer;
	ID3D12Resource* depthStencilBuffer;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;

	ConstantBuffer cbPerObject; // this is the constant buffer data we will send to the gpu

	UINT8* cbvGPUAddress[frameBufferCount]; // this is a pointer to the memory location we get when we map our constant buffer

	// Cube rendering stuff

	DirectX::XMFLOAT4X4 cameraProjMat; // this will store our projection matrix
	DirectX::XMFLOAT4X4 cameraViewMat; // this will store our view matrix

	DirectX::XMFLOAT4 cameraPosition; // this is our cameras position vector
	DirectX::XMFLOAT4 cameraTarget; // a vector describing the point in space our camera is looking at
	DirectX::XMFLOAT4 cameraUp; // the worlds up vector

	DirectX::XMFLOAT4X4 cube1WorldMat; // our first cubes world matrix (transformation matrix)
	DirectX::XMFLOAT4X4 cube1RotMat; // this will keep track of our rotation for the first cube
	DirectX::XMFLOAT4 cube1Position; // our first cubes position in space

	DirectX::XMFLOAT4X4 cube2WorldMat; // our first cubes world matrix (transformation matrix)
	DirectX::XMFLOAT4X4 cube2RotMat; // this will keep track of our rotation for the second cube
	DirectX::XMFLOAT4 cube2PositionOffset; // our second cube will rotate around the first cube, so this is the position offset from the first cube

	int numCubeIndices; // the number of indices to draw the cube

public:
	static Renderer* getInstance();

	bool InitD3D(); // initializes Direct3D 12
	
	void Update(); // update the game logic

	void UpdatePipeline(); // update the direct3d pipeline (update command lists)

	void Render(); // execute the command list

	void Cleanup(); // release com ojects and clean up memory

	void WaitForPreviousFrame(); // wait until gpu is finished with command list
};

