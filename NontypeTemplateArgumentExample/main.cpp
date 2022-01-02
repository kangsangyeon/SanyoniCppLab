// https://gamedevforever.com/343?category=387043

/*
 * ������ ���ø� �Ű������� �̿��Ͽ� �پ��� ���� ������ �ϴ� ��Ÿ �Լ��� �ۼ��մϴ�.
 * ���� �� ���� �Լ����� ��Ÿ�ӿ��� ����Ǵ� ���� �ƴϰ�, ������Ÿ�ӿ� ���Ǿ� ���� �ڵ�� ġȯ�˴ϴ�.
 * ���� �Ű������� ������ Ÿ�ӿ� Ȯ�� ������ ����� ������ �����մϴ�.
 * ���Ǿ� �̸� ���ǵ� �ʿ䰡 �ִ� ��� �Ǵ� ��� �迭�� �����ϴ� �� ����ϱ� �����ϴ�.
 */

#include <iostream>

template <int _left, int _right>
struct add
{
	enum { value = _left + _right };
};

/*
 * pow ��Ÿ �Լ��� _base�� _exponent���� ���ϴ� �Լ��Դϴ�. (=�ŵ� ���� �Լ��Դϴ�.)
 * ���� power ���� �ڵ�ó�� ����Լ��� ���� ������ �����մϴ�.
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
