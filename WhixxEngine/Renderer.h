#pragma once

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

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	ID3D12DescriptorHeap* rtvDescriptorHeap;
	ID3D12DescriptorHeap* dsDescriptorHeap;

	ID3D12Resource* renderTargets[frameBufferCount];
	ID3D12Resource* vertexBuffer;
	ID3D12Resource* indexBuffer;
	ID3D12Resource* depthStencilBuffer;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;

public:
	static Renderer* getInstance();

	bool InitD3D(); // initializes Direct3D 12
	
	void Update(); // update the game logic

	void UpdatePipeline(); // update the direct3d pipeline (update command lists)

	void Render(); // execute the command list

	void Cleanup(); // release com ojects and clean up memory

	void WaitForPreviousFrame(); // wait until gpu is finished with command list
};

