#pragma once

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE _hInstance, string _windowTitle, string _windowClass, int _width, int _height);
	bool ProcessMessages();
	HWND GetHWND() const;
	~RenderWindow();
private:
	void RegisterWindowClass();

private:
	HWND handle = NULL;				//�� â�� �ڵ�
	HINSTANCE hInstance = NULL;		//�ν��Ͻ� ���ø����̼��� �ڵ�
	string windowTitle = "";
	wstring windowTitleWide = L"";
	string windowClass = "";
	wstring windowClassWide = L"";
	int width = 0;
	int height = 0;
};

