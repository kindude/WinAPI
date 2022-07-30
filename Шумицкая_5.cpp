// Шумицкая_5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Шумицкая_5.h"
#include <iostream>
#include <commdlg.h>
#include <string.h>
#define IDR_MENU1 129
#define PageSize 32775
#define Percent 32776
#define SysCatalog 32777
#define Attributes 32778


using namespace std;




// --- Прототип оконной функции главного окна
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;

TCHAR ClassName1[] = "Windows Class";
TCHAR AppTitle1[] = "Главное окно группа АСУ-19 Шумицкая ";


HWND hMainWnd;

WNDCLASS wc_main;
HBRUSH FIRST_BRUSH, SECOND_BRUSH;



//HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	FIRST_BRUSH = CreateSolidBrush(RGB(255, 255, 255));

	SECOND_BRUSH = CreateSolidBrush(RGB(255, 255, 255));

	MSG msg;


	HMENU hMenu;
	hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1));

	int m_width, m_height;
	m_width = GetSystemMetrics(SM_CXFULLSCREEN);
	m_height = GetSystemMetrics(SM_CYFULLSCREEN);

	// Главное окно

	if ((hMainWnd = FindWindow(ClassName1, NULL)) != NULL)
	{

		// Если прилож. было запущено ранее, активизировать
		// и выдвинуть на передний план его главное окно
		int msgID1 = MessageBox(hMainWnd, "Приложение уже запущено хотите продолжить?", "Информация", MB_OKCANCEL);
		switch (msgID1)
		{
		case IDOK:

			if (IsIconic(hMainWnd))
			{
				ShowWindow(hMainWnd, SW_RESTORE);
			}
			break;

		case IDCANCEL:
			PostQuitMessage(0);
			DestroyWindow(hMainWnd);
			break;
		}

		return FALSE;
	}


	hInst = hInstance; // Сохран. дескриптора экз. прилож.


	ZeroMemory(&wc_main, sizeof(wc_main)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc_main.lpszClassName = ClassName1; // Имя класса окон
	//Адрес оконной ф-ции
	wc_main.lpfnWndProc = (WNDPROC)MainWndProc;
	wc_main.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // Стиль класса окон
	wc_main.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc_main.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	// Курсор мыши для окон
	wc_main.hCursor = LoadCursor(NULL, IDC_PERSON);
	// Кисть для окон
	wc_main.hbrBackground = FIRST_BRUSH;
	wc_main.lpszMenuName = NULL; // Ресурс меню окон
	wc_main.cbClsExtra = 0; // Дополнительная память класса
	wc_main.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	RegisterClass(&wc_main);
	// Создание главного окна приложения.
	hMainWnd = CreateWindow(
		ClassName1, // Имя класса окон
		AppTitle1, // Заголовок окна
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // Стиль окна
		0, // X-координата
		0, // Y-координата
		m_width, // Ширина окна
		m_height, // Высота окна
		NULL, // Дескриптор окна-родителя
		NULL, // Дескриптор меню окна
		hInst, // Дескриптор экз. приложения
		NULL); // Дополнительная информация




	if (!hMainWnd)
	{
		// Окно не создано, выдается сообщение.
		MessageBox(NULL, "Window create error", AppTitle1, MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	// Отображение окна и обновление его
	ShowWindow(hMainWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hMainWnd);
	SetMenu(hMainWnd, hMenu);
	// Запуск цикла обработки очереди сообщений.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Преобразов. сообщений клавиатуры в символьные
		TranslateMessage(&msg);
		// Отправление сообщения оконной функции
		DispatchMessage(&msg);
	}
	return msg.wParam; // Завершение работы приложения





}


//Оконнная функция главного окна

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	SYSTEM_INFO si;
	DWORD Pagesize,percent,ATR;
	MEMORYSTATUSEX MemStat;
	OPENFILENAME ofn;
	char szFileName[260];
	HANDLE hFile;
	char Page[20];
	char percantage[20];
	char cBufferForSystemDirectory[100];
	char atr[200];
	LPSTR print;

	switch (uMsg)
	{


	case WM_CREATE:





		break;
	case WM_COMMAND:
	{
		UINT idItem = LOWORD(wParam);
		switch (idItem)
		{
		case PageSize:
			GetSystemInfo(&si);
			
			Pagesize = si.dwPageSize;
			sprintf_s(Page, "%d %s", Pagesize,"Байт");
			
			MessageBox(hWnd, Page, "Размер страницы", MB_OK);

			break;

		case Percent:

			MemStat.dwLength = sizeof(MEMORYSTATUSEX);
			GlobalMemoryStatusEx(&MemStat);
			percent = MemStat.dwMemoryLoad;

			sprintf_s(percantage, "%d %s", percent, "Процентов");

			MessageBox(hWnd, percantage, "Процент использования памяти", MB_OK);

			break;

		case SysCatalog:
			GetSystemDirectory(cBufferForSystemDirectory, 256);
			
			MessageBox(hWnd, cBufferForSystemDirectory, "Информация о системном каталоге", MB_OK);

			break;
		case Attributes:

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hMainWnd;
			ofn.lpstrFile = szFileName;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFileName);
			ofn.lpstrFilter = "Все\0*.*\0Текстовые\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			GetOpenFileName(&ofn);

			if (INVALID_HANDLE_VALUE == (hFile = CreateFile(ofn.lpstrFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
			{
				MessageBox(hWnd, "Не могу открыть файл", "Ошибка открытия файла", MB_OK);
				return 0;
			}
			else {

				ATR = GetFileAttributes(ofn.lpstrFile);
				sprintf_s(atr, "%p", ATR);
				
				MessageBox(hWnd,atr, " Информация о файле", MB_OK);

			}


			break;

		}
		break;
	}
	case WM_DESTROY:

		PostQuitMessage(0);
		break;




	default:

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
