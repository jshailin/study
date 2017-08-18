//��дһ������ʵ�֣����ļ�
#include <windows.h>
#include <tchar.h>
#include <winuser.h>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WindowClass;	//����������ṹ

	static LPCTSTR szAppName{ _T("FWin") };	//����������
	HWND hWnd;	//���ھ��
	MSG msg;	//����

#pragma region �����������ֵ
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;	//��Ϣ������
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	WindowClass.lpszMenuName = nullptr;
	WindowClass.lpszClassName = szAppName;	//������
	WindowClass.hIconSm = nullptr;
#pragma endregion

	//ע�ᴰ������
	RegisterClassEx(&WindowClass);

	//��������
	hWnd = CreateWindow(szAppName, _T("����д����"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

	//��ʾ����
	ShowWindow(hWnd, nCmdShow);

	//�ػ����ڿͻ���
	UpdateWindow(hWnd);

	//��Ϣѭ��
	while (GetMessage(&msg, nullptr, 0, 0) == TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);	//����������WINDOWSϵͳ
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:	//�����ػ��ͻ���
			HDC hDC;	//��ʾ������
			PAINTSTRUCT Paintst;
			RECT aRect;	//������
			hDC = BeginPaint(hWnd, &Paintst);

			//ȡ�ù�����
			GetClientRect(hWnd, &aRect);

			SetBkMode(hDC, TRANSPARENT);	//���ñ���

			DrawText(hDC, _T("���������Ǹ����ڣ�"), -1, &aRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hWnd, &Paintst);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);	//����һ��WM_QUIT��Ϣ
			return 0;
		default:
	return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
