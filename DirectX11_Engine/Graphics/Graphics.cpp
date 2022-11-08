#include "../stdafx.h"
#include "Graphics.h"

bool Graphics::Initialize(HWND _hWnd, int _width, int _height)
{
	if (!InitializeDirectX(_hWnd, _width, _height))
	{
		return false;
	}

	if (!InitializeShaders())
	{
		return false;
	}

	if (!InitializeScene())
	{
		return false;
	}

	return true;
}

void Graphics::Render()
{
	float bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), bgColor);
	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	deviceContext->IASetInputLayout(vertexShader.GetInputLayout());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->RSSetState(rasterizerState.Get());
	deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);
	deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
	deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	//green Tri
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer2.GetAddressOf(), &stride, &offset);
	deviceContext->Draw(3, 0);

	//red Tri
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->Draw(3, 0);

	//Draw Text
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), L"HELLO WORLD", DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	spriteBatch->End();

	swapChain->Present(1, NULL);
}

bool Graphics::InitializeDirectX(HWND _hWnd, int _width, int _height)
{
	vector<AdapterData> adapters = AdapterReader::GetAdapters();

	if (adapters.size() < 1)
	{
		ErrorLogger::Log("No IDXGI Adapters found.");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = _width;
	scd.BufferDesc.Height = _height;
	scd.BufferDesc.RefreshRate.Numerator = 144;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = _hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, NULL, NULL, NULL, 0, D3D11_SDK_VERSION, &scd, swapChain.GetAddressOf(), device.GetAddressOf(), NULL, deviceContext.GetAddressOf());

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create device and swapchain.");
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "GetBuffer Failed.");
		return false;
	}

	hr = device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create render target view.");
		return false;
	}

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = _width;
	depthStencilDesc.Height = _height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthStencilDesc, NULL, depthStencilBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stecil buffer.");
		return false;
	}

	hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil view.");
		return false;
	}

	deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

	//Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hr = device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil state.");
		return false;
	}

	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = _width;
	viewport.Height = _height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	deviceContext->RSSetViewports(1, &viewport);

	//Create Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	//rasterizerDesc.FrontCounterClockwise = FALSE;
	hr = device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create rasterizer state.");
		return false;
	}

	spriteBatch = make_unique<DirectX::SpriteBatch>(deviceContext.Get());
	spriteFont = make_unique<DirectX::SpriteFont>(device.Get(), L"Data/Fonts/comic_sans_ms_16.spritefont");


	return true;
}

bool Graphics::InitializeShaders()
{
	wstring shaderFolder = L"";
#pragma region DetermineShaderPath
#ifdef _DEBUG //Debug mode
	#ifdef _WIN64 //x64
		shaderFolder = L"..\\x64\\Debug\\";
	#else //x86
		shaderFolder = L"..\\Debug\\";
	#endif
#else //Release mode
	#ifdef _WIN64 //x64
		shaderFolder = L"..\\x64\\Release\\";
	#else //x86
		shaderFolder = L"..\\Release\\";
	#endif
#endif
#pragma endregion DetermineShaderPath


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT numElements = ARRAYSIZE(layout);

	if (!vertexShader.Initialize(device, shaderFolder + L"VertexShader.cso", layout, numElements))
	{
		return false;
	}

	if (!pixelShader.Initialize(device, shaderFolder + L"PixelShader.cso"))
	{
		return false;
	}

	return true;
}

bool Graphics::InitializeScene()
{

	Vertex vertices[] =
	{	
		Vertex(-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f), //Bottom Left
		Vertex(0.0f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f), //Top Middle 
		Vertex(0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f), //Bottom Right
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = vertices;

	HRESULT hr = this->device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->vertexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create vertex buffer.");
		return false;
	}

	Vertex vertices2[] =
	{
		Vertex(-0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f), //Bottom Left
		Vertex(0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f), //Top Middle 
		Vertex(0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f), //Bottom Right
	};

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;


	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = vertices2;

	 hr = this->device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->vertexBuffer2.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create vertex buffer.");
		return false;
	}

	return true;
}



