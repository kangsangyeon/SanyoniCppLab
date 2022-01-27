/*
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 * https://wikidocs.net/501
 */

#include <iostream>

/*
 * 가장 간단한 형태의 CRTP입니다.
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
 * CRTP를 응용한 예제로, 어떤 타입의 인스턴스 개수를 추적하는 예제입니다.
 */

template <typename CountedType>
class ObjectCounter
{
private:
	static size_t count; // 존재하는 객체 수

protected:
	// 기본 생성자
	ObjectCounter() { ++ObjectCounter<CountedType>::count; }

	// 복사 생성자 
	ObjectCounter(ObjectCounter<CountedType> const&) { ++ObjectCounter<CountedType>::count; }

	// 소멸자
	~ObjectCounter() { --ObjectCounter<CountedType>::count; }

public:
	// 존재하는 객체 수를 반환 
	static size_t live() { return ObjectCounter<CountedType>::count; }
};

// 카운터를 0으로 초기화
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
 * 일반적으로 상속만으로 구현할 수 없는 Static Polymorphism을 흉내낼 수도 있습니다.
 * 이러한 CRTP의 사용을 simulated dynamic binding이라고 부르기도 합니다.
 */
template <class TDerived>
struct Base
{
	void interface()
	{
		// override처럼 동작하길 원하는 함수가 
		// static 함수가 아닌 경우, 이렇게 type cast하여 호출할 수 있습니다.
		static_cast<TDerived*>(this)->implementation();
	}

	static void static_func()
	{
		// 이런식으로 static polymorphism을 흉내낼 수 있습니다.
		TDerived::static_sub_func();
	}
};

struct Derived : Base<Derived>
{
	void implementation();
	static void static_sub_func();
};
