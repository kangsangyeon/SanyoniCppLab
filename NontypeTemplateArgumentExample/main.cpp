// https://gamedevforever.com/343?category=387043

/*
 * 비형식 템플릿 매개변수를 이용하여 다양한 수학 연산을 하는 메타 함수를 작성합니다.
 * 물론 이 수학 함수들은 런타임에서 실행되는 것이 아니고, 컴파일타임에 계산되어 실제 코드와 치환됩니다.
 * 따라서 매개변수로 컴파일 타임에 확인 가능한 상수만 전달이 가능합니다.
 * 계산되어 미리 정의될 필요가 있는 상수 또는 상수 배열을 정의하는 데 사용하기 좋습니다.
 */

#include <iostream>

template <int _left, int _right>
struct add
{
	enum { value = _left + _right };
};

/*
 * pow 메타 함수는 _base의 _exponent승을 구하는 함수입니다. (=거듭 제곱 함수입니다.)
 * 다음 power 구현 코드처럼 재귀함수와 같이 구현이 가능합니다.
 */

template <int _base, int _exponent>
struct power
{
	enum : unsigned long long { value = _base * power<_base, _exponent - 1>::value };
};

template <int _base>
struct power<_base, 0>
{
	enum : unsigned long long { value = 1 };
};

/*
 * factorial
 */

template <int _number>
struct factorial
{
	enum : unsigned long long { value = _number * factorial<_number - 1>::value };
};

template <>
struct factorial<1>
{
	enum : unsigned long long { value = 1 };
};

/*
 * fibonacci_sequence
 */

template <int _index>
struct fibonacci_sequence
{
	enum : unsigned long long { value = fibonacci_sequence<_index - 1>::value + fibonacci_sequence<_index - 2>::value };
};

template <>
struct fibonacci_sequence<0>
{
	enum : unsigned long long { value = 0 };
};

template <>
struct fibonacci_sequence<1>
{
	enum : unsigned long long { value = 1 };
};

/*
 * Test Functions
 */

void TestAdd()
{
	std::cout << "add<10, 100>::value = " << add<10, 100>::value << std::endl;
	std::cout << "add<999, 1>::value = " << add<999, 1>::value << std::endl;
	std::cout << std::endl;
}

void TestPower()
{
	std::cout << "power<2, 3>::value = " << power<2, 3>::value << std::endl;
	std::cout << "power<5, 2>::value = " << power<5, 2>::value << std::endl;
	std::cout << "power<555, 100>::value = " << power<555, 100>::value << std::endl;
	std::cout << std::endl;
}

void TestFactorial()
{
	std::cout << "factorial<5>::value = " << factorial<5>::value << std::endl;
	std::cout << "factorial<20>::value = " << factorial<20>::value << std::endl;
	std::cout << "factorial<50>::value = " << factorial<50>::value << std::endl;
	std::cout << std::endl;
}

void TestFibonacciSequence()
{
	std::cout << "fibonacci_sequence<5>::value = " << fibonacci_sequence<5>::value << std::endl;
	std::cout << "fibonacci_sequence<20>::value = " << fibonacci_sequence<20>::value << std::endl;
	std::cout << "fibonacci_sequence<50>::value = " << fibonacci_sequence<50>::value << std::endl;
	std::cout << std::endl;
}

int main()
{
	TestAdd();
	TestPower();
	TestFactorial();
	TestFibonacciSequence();

	return 0;
}
