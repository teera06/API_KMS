#pragma once
// ���δ� std�� ������̴�.
#include <string>
#include <string_view>

// ��� : ���ڿ� �빮�� ��ȯ
class EngineString
{
public:
	static std::string ToUpper(std::string_view View);
	// string_view ����ϴ� ����?
	// std : stringŸ���� ���纻 ���� ���� ȿ�������� ����
	// std : stringŸ���� ���纻 ������ ������ ȿ������ ����?
	// std : string���� ������ �ᱹ vector<char>�� ����.
	// vector<char>�ȿ����� �����Ҵ��� �̷����Ƿ�
	// ���ڿ� ���̰� ��������� ���纻�� ����°��� �δ��� ũ��.
protected:

private:
	// constrcuter destructer
	EngineString();
	~EngineString();

	// delete Function
	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString&& _Other) noexcept = delete;
	EngineString& operator=(const EngineString& _Other) = delete;
	EngineString& operator=(EngineString&& _Other) noexcept = delete;
};

