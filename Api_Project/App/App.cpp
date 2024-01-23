#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineWindow.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineWindow::Init(hInstance);

	EngineWindow NewWindow0;
	NewWindow0.Open();

	EngineWindow::WindowMessageLoop();
}