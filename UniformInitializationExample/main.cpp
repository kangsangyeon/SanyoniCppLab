#include <iostream>

class A
{
public:
	A() { std::cout << "A constructor called." << std::endl; }
};

class B
{
public:
	B() { std::cout << "B constructor called." << std::endl; }
};

class C
{
public:
	C(int _value) { std::cout << "C constructor called: " << _value << std::endl; }
};

int main()
{
	// 컴파일러는 아래 코드를 A의 객체 a를 만든 것이 아니라,
	// A를 리턴하며 매개변수를 받지 않는 함수 a를 정의한 것으로 해석합니다.
	A a();
	A resultA = a();	// 이렇게 말입니다.

	// 아래 코드는 마치 A 타입 객체를 생성하고 매개변수로 넘기며 B타입의 b라는 객체를 생성한 것처럼 보이지만,
	// 사실은 인자로 A를 리턴하고 인자가 없는 함수를 받으며, 리턴 타입이 B인 함수 b를 정의한 것입니다.
	B b(A ());
	B resultB = b(a);	// 이렇게 말입니다.

	// 이렇게 우리가 생각한 것과는 다르게 동작하는 경우가 있습니다.
	// 이러한 문제가 발생하는 것은 ()가 함수의 매개변수를 정의하는데도 사용되고
	// 그냥 일반적인 객체의 생성자를 호출하는데도 사용되기 때문입니다.
	// 따라서 C++11에서는 이러한 문제를 해결하기 위해 uniform initialization이라는 것을 도입했습니다.

	// 중괄호를 이용해서 생성자를 호출합니다.
	A a2{};

	// uniform initialization를 이용한 생성과 ()를 이용한 생성의 경우 한 가지 큰 차이점이 있는데
	// 바로 일부 암시적 타입 변환을 불허한다는 점입니다.
	// uniform initialization을 이용해서 생성자를 호출하는 경우,
	// narrowing conversions(=축소 변환, 데이터 손실이 있는 변환)을 허용하지 않습니다.
	// 따라서 {}를 사용하게 된다면, 원하지 않는 타입 캐스팅을 방지해서 미연에 오류를 잡아낼 수 있습니다.
	C _c1(3.5);

	// 컴파일 오류!
	// C _c2{3.5};

	class D
	{
	public:
		// D()
	};

	return 0;
}
