/*
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 * https://wikidocs.net/501
 */

#include <iostream>

/*
 * ���� ������ ������ CRTP�Դϴ�.
 */
template <typename TClass>
class SimpleBase
{
};

class SimpleDerived : public SimpleBase<SimpleDerived>
{
};

/*
 * Object Counter
 * CRTP�� ������ ������, � Ÿ���� �ν��Ͻ� ������ �����ϴ� �����Դϴ�.
 */

template <typename CountedType>
class ObjectCounter
{
private:
	static size_t count; // �����ϴ� ��ü ��

protected:
	// �⺻ ������
	ObjectCounter() { ++ObjectCounter<CountedType>::count; }

	// ���� ������ 
	ObjectCounter(ObjectCounter<CountedType> const&) { ++ObjectCounter<CountedType>::count; }

	// �Ҹ���
	~ObjectCounter() { --ObjectCounter<CountedType>::count; }

public:
	// �����ϴ� ��ü ���� ��ȯ 
	static size_t live() { return ObjectCounter<CountedType>::count; }
};

// ī���͸� 0���� �ʱ�ȭ
template <typename CountedType>
size_t ObjectCounter<CountedType>::count = 0;

template <typename CharT>
class MyString : public ObjectCounter<MyString<CharT>>
{
};

int main()
{
	MyString<char> s1, s2;
	MyString<wchar_t> ws;
	std::cout << "number of MyString<char>: "
		<< MyString<char>::live() << std::endl;
	std::cout << "number of MyString<wchar_t>: "
		<< ws.live() << std::endl;
}

/*
 * Static polymorphism
 * �Ϲ������� ��Ӹ����� ������ �� ���� Static Polymorphism�� �䳻�� ���� �ֽ��ϴ�.
 * �̷��� CRTP�� ����� simulated dynamic binding�̶�� �θ��⵵ �մϴ�.
 */
template <class TDerived>
struct Base
{
	void interface()
	{
		// overrideó�� �����ϱ� ���ϴ� �Լ��� 
		// static �Լ��� �ƴ� ���, �̷��� type cast�Ͽ� ȣ���� �� �ֽ��ϴ�.
		static_cast<TDerived*>(this)->implementation();
	}

	static void static_func()
	{
		// �̷������� static polymorphism�� �䳻�� �� �ֽ��ϴ�.
		TDerived::static_sub_func();
	}
};

struct Derived : Base<Derived>
{
	void implementation();
	static void static_sub_func();
};
