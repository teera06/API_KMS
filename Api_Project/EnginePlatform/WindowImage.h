#pragma once
#include <EngineBase\PathObject.h>
#include <Windows.h>

// ���� :
class UWindowImage : public UPathObject
{
public:
	// constrcuter destructer
	UWindowImage();
	~UWindowImage();

	// delete Function
	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	// bool�� �����ؼ� false�� ���� true�� ����
	bool Load(HDC _MainDC);

protected:

private:
	// �����쿡�� �������ִ� H���� �ֵ��� �� struct HBITMAP__{int unused;}; typedef struct HBITMAP__ *HBITMAP
	// �������̸鼭 8����Ʈ �����Դϴ�.
	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP Info = BITMAP();
};

