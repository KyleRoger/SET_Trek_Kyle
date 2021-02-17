
#include <Windows.h>
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"
#include "Mouse.h"
Graphics* graphics;

#define MINI_GAME 1
#define GAME_END -1
#define ALL_GOOD 0

LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY ||
		msg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (msg == WM_LBUTTONDOWN)
	{
		float x = LOWORD(lparam);
		float y = HIWORD(lparam);

		Mouse::mouseX = x;
		Mouse::mouseY = y;
		Mouse::IsClick = true;

	}
	else if (msg == WM_KEYDOWN)
	{
		Mouse::keyboardSelection = wparam;
	}
	return DefWindowProc(handle, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WinProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; //Alert - This is useful here... what does it do?

	RegisterClassEx(&windowclass);


	RECT rect = { 0, 0, 1024, 768 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "SET Trek", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle)
	{
		return 1;
	}

	float width = 0;
	float height = 0;
	if (GetClientRect(windowhandle, &rect))
	{
		width = float(rect.right - rect.left);
		height = float(rect.bottom - rect.top);
	}


	graphics = new Graphics();
	graphics->SetWindowSize(rect);
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}


	Mouse::Init();

	GameLevel::Init(graphics);
	ShowWindow(windowhandle, nCmdShow);
	GameController::LoadInitialLevel(new Level1());

	Level1* theLevel = new Level1();
	theLevel->SetWindowWidth(width);
	theLevel->SetWindowHeight(height);

	MSG message;
	int gameState = 0;
	bool gameEnd = false;
	bool miniGame = false;
	message.message = WM_NULL; //Do not have this set to WM_QUIT, which has a specific context
	while (message.message != WM_QUIT && !gameEnd)
	{
		miniGame = false;

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			//This allows us to send a message to the WindowProc IF there is one
			DispatchMessage(&message);
		else
		{
			//Update Routine... we've moved the code for handling updates to GameController
			gameState = GameController::Update(); //Whrere the screen is updated.

			if (gameState == GAME_END)
			{
				gameEnd = true;
			}
			else if (gameState == MINI_GAME)
			{
				miniGame = true;
			}
			//Render Routine... This is very modular. GameController now handles the rendering
			graphics->BeginDraw();
			GameController::Render(miniGame);
			graphics->EndDraw();

		}
	}

#pragma endregion
	delete graphics;
	return 0;
}