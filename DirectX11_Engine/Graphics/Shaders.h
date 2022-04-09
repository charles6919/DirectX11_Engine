#pragma once

class VertexShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	ID3D11InputLayout* GetInputLayout();
	
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

class PixelShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPath);
	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetBuffer();

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer = nullptr;
};

