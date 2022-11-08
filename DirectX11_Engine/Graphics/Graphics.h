#pragma once
#include "AdapterReader.h"
#include "Shaders.h"
#include "Vertex.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>

class Graphics
{
public:
	bool Initialize(HWND _hWnd, int _width, int _height);
	void Render();
private:
	bool InitializeDirectX(HWND _hWnd, int _width, int _height);
	bool InitializeShaders();
	bool InitializeScene();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;


	VertexShader vertexShader;
	PixelShader pixelShader;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer2;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
	
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;

	unique_ptr<DirectX::SpriteBatch> spriteBatch;
	unique_ptr<DirectX::SpriteFont> spriteFont;
};

