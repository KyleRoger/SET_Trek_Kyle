#pragma once

#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")

#include<Windows.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <d3d11_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
#include <d3d11.h>

class Graphics
{
	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory* factory; //The factory allows us to create many other types of D2D resources
	ID2D1HwndRenderTarget* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!
	RECT windowSize;
	float windowWidth;
	float windowHeight;

public:
	Graphics();


	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return rendertarget;
	}

	ID2D1DeviceContext* GetDeviceContext()
	{
		ID2D1DeviceContext *rtDC;
		rendertarget->QueryInterface(&rtDC);
		return rtDC;
	}

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);

	//Device
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	//Render Target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;

	float GetWindowWidth(void);
	float GetWindowHeight(void);
	RECT GetWindowSize(void);
	void SetWindowSize(RECT size);

};
