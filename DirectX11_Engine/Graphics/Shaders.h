#pragma once

class VertexShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPath);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer = nullptr;
};

