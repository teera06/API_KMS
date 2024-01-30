#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>

// 윈도우에서 이미지를 사용하기 위해서 지원하는 라이브러리.
// 헤더랑 다르게 라이브러리는 #pragma comment 통해서 추가 해야 한다.
#pragma comment(lib, "Msimg32.lib")

UWindowImage::UWindowImage()
{
}

UWindowImage::~UWindowImage()
{
}

bool UWindowImage::Load(HDC _MainDC)
{
	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	if (".BMP" == UpperExt)
	{
		//HINSTANCE hInst,  이 이미지를 사용할 프로그램을 알려달라는건데. nullptr넣어도 괜찮다.
		//LPCSTR name, // 경로
		//UINT type, // 이미지 타입
		//int cx, // 이미지를 로드할 크기 X 0을 넣으면 전체 크기로 로드
		//int cy, // 이미지를 로드할 크기 Y 0을 넣으면 전체 크기로 로드
		//UINT fuLoad 로드 옵션

		// 비트맵을 제어할수 있는 핸들입니다.
		// 비트맵을 그릴수 있는 핸들은 아닙니다.
		// 그린다는 목적을 가진 핸들과
		// 비트맵을 로드한다는 목적의 핸들이 다르다는 것입니다.
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		BitMap = (HBITMAP)ImageHandle;
	}
	else if (".PNG" == UpperExt)
	{
		MsgBoxAssert("아직 로드를 지원하지 않는 포맷입니다");
	}

	// 그릴수있고 이미지에 간섭할수 있는 권한이다.
	// 어디에 그릴거냐.
	// 어디속해서 어디에 그려질 DC냐를 넣어줘야 합니다.
	// 당연히 하나뿐인 mainwindow의 DC를 넣어주면 됩니다.
	// 그릴수 있는 권한이 자신이 뭘 그려야하는지를 알려줘야 합니다.
	// ImageDC야 너는 BitMap그려야 해.
	ImageDC = CreateCompatibleDC(_MainDC);
	HBITMAP OldBitMap = (HBITMAP)SelectObject(ImageDC, BitMap);
	// 사용법이 정말 
	DeleteObject(OldBitMap);

	// ImageDC를 만들면 내부에서 1,1크기의 HBITMAP을 만든다.



	// 두가지를 사용할건데.
	// Png때와 bmp일대 로드하는 방식이 달라요.

	return true;
}