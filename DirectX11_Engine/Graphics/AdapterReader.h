#pragma once
class AdapterData
{
public:
	AdapterData(IDXGIAdapter* _pAdapter);
	IDXGIAdapter* pAdapter;
	DXGI_ADAPTER_DESC description;
};

class AdapterReader
{
public:
	static vector<AdapterData> GetAdapters();

private:
	static vector<AdapterData> adapters;
};

