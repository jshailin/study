//手写一个窗口实现，单文件
#include <windows.h>
#include <tchar.h>
#include <winuser.h>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WindowClass;	//窗口类参数结构

	static LPCTSTR szAppName{ _T("FWin") };	//窗口类名字
	HWND hWnd;	//窗口句柄
	MSG msg;	//窗口

#pragma region 窗口类参数赋值
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;	//消息处理函数
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	WindowClass.lpszMenuName = nullptr;
	WindowClass.lpszClassName = szAppName;	//类型名
	WindowClass.hIconSm = nullptr;
#pragma endregion

	//注册窗口类型
	RegisterClassEx(&WindowClass);

	//创建窗口
	hWnd = CreateWindow(szAppName, _T("纯手写窗口"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

	//显示窗口
	ShowWindow(hWnd, nCmdShow);

	//重画窗口客户区
	UpdateWindow(hWnd);

	//消息循环
	while (GetMessage(&msg, nullptr, 0, 0) == TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);	//结束，返回WINDOWS系统
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:	//处理重画客户区
			HDC hDC;	//显示上下文
			PAINTSTRUCT Paintst;
			RECT aRect;	//工作区
			hDC = BeginPaint(hWnd, &Paintst);

			//取得工作区
			GetClientRect(hWnd, &aRect);

			SetBkMode(hDC, TRANSPARENT);	//设置背景

			DrawText(hDC, _T("哈哈，我是个窗口！"), -1, &aRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hWnd, &Paintst);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);	//产生一个WM_QUIT消息
			return 0;
		default:
	return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
