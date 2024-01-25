#pragma once
// Ű���带 �������ִ� �� OS�ϰ��̱� ������
// �Է¿� ���� �Լ��� �翬�� OS�� �츮���� �����ؾ� �մϴ�.
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>

// AllStateClass
// ��� : �Է�Ű�� Map�� ���� �ڷᱸ�� ���� �� �Է�Ű�� ���� ����
class EngineInput
{
	friend class InputInitCreator; //InputInitCreatorŬ�������� private:�ΰ͵� ����

private:
	class /*EngineInput::*/EngineKey
	{
		friend EngineInput;

	public:
		// �Է� ����
		bool Down = false; // ���� ����
		bool Press = false; // ��� ������
		bool Up = false; // ������ ����
		bool Free = true; // ������ ������

		float PressTime = 0.0f; // ����

		int Key = -1; // VK_LBUTTON // �⺻ Ű��

		void KeyCheck(); // ���� Ű �Է� ���¿� ���� ���� �Է� ���� ��ȭ

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key) // �����ڿ��� Ű���� �޾ƿ�
		{

		}
	};

public:
	// constrcuter destructer
	EngineInput();
	~EngineInput();

	// delete Function
	EngineInput(const EngineInput& _Other) = delete;
	EngineInput(EngineInput&& _Other) noexcept = delete;
	EngineInput& operator=(const EngineInput& _Other) = delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept = delete;

	static bool IsDown(int _Key) // Ű���� ����
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Free;
	}

	static void KeyCheckTick(float _DeltaTime);

protected:
	//              'A'  ���°� �?
	static std::map<int, EngineKey> AllKeys; // Key�� ����� map���� ����

	int Value;

private:
	static void InputInit();
};

