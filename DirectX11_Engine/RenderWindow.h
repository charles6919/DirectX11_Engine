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
	HWND handle = NULL;				//이 창의 핸들
	HINSTANCE hInstance = NULL;		//인스턴스 애플리케이션의 핸들
	string windowTitle = "";
	wstring windowTitleWide = L"";
	string windowClass = "";
	wstring windowClassWide = L"";
	int width = 0;
	int height = 0;
};

