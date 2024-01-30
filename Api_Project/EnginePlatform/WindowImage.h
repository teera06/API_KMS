#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// 우리 엔진 WinAPi단계에서 랜더링이라는것은
// 이미지가 다른 이미지를 자신내부에 그리는 겁니다.
// DC라는게 외부로 드러나면 안됩니다.
// DC를 통해서 그리는 모든 책임은 오로지 => UWindowImage가 모두 담당한다.

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UEngineWindow;
// 설명 :
class UWindowImage : public UPathObject
{
	friend UEngineWindow;

public:
	// constrcuter destructer
	UWindowImage();
	~UWindowImage();

	// delete Function
	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	// bool을 리턴해서 false면 실패 true면 성공
	bool Load(UWindowImage* _Image);

	FVector GetScale(); // BITMAP X,Y -> 크기 반환

	// 윈도우 랜더링의 핵심 인터페이스중 하나인 HDC를 외부에 공개할 필요는 굳이 없어.
	//HDC GetImageDC()
	//{
	//	return ImageDC;
	//}

	// UWindowImage* _Copy 이 이미지를
	// FTransform _Trans 이 위치와 크기로
	// 나한테 카피해라.
	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans); // 이미지 복사

protected:

private:
	// 윈도우에서 지원해주는 H붙은 애들은 다 struct HBITMAP__{int unused;}; typedef struct HBITMAP__ *HBITMAP
	// 포인터이면서 8바이트 정수입니다.
	HBITMAP hBitMap = 0; // 릭이 생김 -> 소멸자에서 제거
	HDC ImageDC = 0; // 이미지를 그릴 권한, 릭이 생김 -> 소멸자에서 제거
	BITMAP BitMapInfo = BITMAP(); // 비트맵를 담는 구조체인데 이걸 얻어와야 합니다.

	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	bool Create(HDC _MainDC);
};

