#pragma once
#include "AdapterReader.h"
#include "Shaders.h"

class Graphics
{
public:
	bool Initialize(HWND _hWnd, int _width, int _height);
	void Render();
private:
	bool InitializeDirectX(HWND _hWnd, int _width, int _height);
	bool InitializeShaders();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	VertexShader vertexShader;

};

