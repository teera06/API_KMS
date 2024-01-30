#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>

// �����쿡�� �̹����� ����ϱ� ���ؼ� �����ϴ� ���̺귯��.
// ����� �ٸ��� ���̺귯���� #pragma comment ���ؼ� �߰� �ؾ� �Ѵ�.
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
		//HINSTANCE hInst,  �� �̹����� ����� ���α׷��� �˷��޶�°ǵ�. nullptr�־ ������.
		//LPCSTR name, // ���
		//UINT type, // �̹��� Ÿ��
		//int cx, // �̹����� �ε��� ũ�� X 0�� ������ ��ü ũ��� �ε�
		//int cy, // �̹����� �ε��� ũ�� Y 0�� ������ ��ü ũ��� �ε�
		//UINT fuLoad �ε� �ɼ�

		// ��Ʈ���� �����Ҽ� �ִ� �ڵ��Դϴ�.
		// ��Ʈ���� �׸��� �ִ� �ڵ��� �ƴմϴ�.
		// �׸��ٴ� ������ ���� �ڵ��
		// ��Ʈ���� �ε��Ѵٴ� ������ �ڵ��� �ٸ��ٴ� ���Դϴ�.
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		BitMap = (HBITMAP)ImageHandle;
	}
	else if (".PNG" == UpperExt)
	{
		MsgBoxAssert("���� �ε带 �������� �ʴ� �����Դϴ�");
	}

	// �׸����ְ� �̹����� �����Ҽ� �ִ� �����̴�.
	// ��� �׸��ų�.
	// �����ؼ� ��� �׷��� DC�ĸ� �־���� �մϴ�.
	// �翬�� �ϳ����� mainwindow�� DC�� �־��ָ� �˴ϴ�.
	// �׸��� �ִ� ������ �ڽ��� �� �׷����ϴ����� �˷���� �մϴ�.
	// ImageDC�� �ʴ� BitMap�׷��� ��.
	ImageDC = CreateCompatibleDC(_MainDC);
	HBITMAP OldBitMap = (HBITMAP)SelectObject(ImageDC, BitMap);
	// ������ ���� 
	DeleteObject(OldBitMap);

	// ImageDC�� ����� ���ο��� 1,1ũ���� HBITMAP�� �����.



	// �ΰ����� ����Ұǵ�.
	// Png���� bmp�ϴ� �ε��ϴ� ����� �޶��.

	return true;
}