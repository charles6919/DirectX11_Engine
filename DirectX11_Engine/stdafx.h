#pragma once
//Library Headers
#include <windows.h>
#include <string>
#include <memory>
#include <functional>
#include <iostream>
#include <wrl/client.h>
#include <vector>

//DirectX headers
#include <d3d11.h>
#include <d3dcompiler.h>

//Libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3DCompiler.lib")

//using namespace
using namespace std;

//Custom Headers
#include "StringConverter.h"
#include "ErrorLogger.h"

