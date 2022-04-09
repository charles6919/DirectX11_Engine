#include "../stdafx.h"
#include "Shaders.h"

bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), this->shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errorMsg = L"Failed to load shader : ";
		errorMsg += shaderPath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

	hr = device->CreateVertexShader(shaderBuffer.Get()->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errorMsg = L"Failed to create vertex shader : ";
		errorMsg += shaderPath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

		hr = device->CreateInputLayout(layoutDesc, numElements, shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), inputLayout.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create input layout.");
		return false;
	}

	return true;
}



ID3D11VertexShader* VertexShader::GetShader()
{
	return shader.Get();
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return shaderBuffer.Get();
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return inputLayout.Get();
}

bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPath)
{
	//Load Pixelshader file
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errMsg = L"Failed to load shader : ";
		errMsg += shaderPath;

		ErrorLogger::Log(hr, errMsg);
		return false;
	}

	//Create Pixelshader
	hr = device->CreatePixelShader(shaderBuffer.Get()->GetBufferPointer(), shaderBuffer.Get()->GetBufferSize(), NULL, shader.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errMsg = L"Failed to create pixel shader : ";
		errMsg += shaderPath;

		ErrorLogger::Log(hr, errMsg);
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return shader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return shaderBuffer.Get();
}
