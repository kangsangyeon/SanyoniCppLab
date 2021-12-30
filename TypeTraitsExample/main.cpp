// https://modoocode.com/295
// https://gamedevforever.com/339?category=387043

/*
 * 템플릿 메타 함수란,
 * 사실 함수는 아니지만 마치 함수처럼 동작하는 템플릿 클래스들을 말합니다.
 *
 * 이들이 메타 함수인 이유는 보통의 함수들은 값에 대해 연산하지만,
 * 메타 함수는 타입에 대해 연산을 수행한다는 점이 다릅니다.
 *
 * 이들은 엄연히 템플릿 클래스이기 때문에, 컴파일 타임에 값이 결정되어 실제 코드에 치환됩니다.
 *
 * 메타 함수의 강점 중 하나로, 메타 함수의 결과값은 값에서부터 타입까지 지원이 가능하다는 점입니다.
 * 타입을 반환하는 메타 함수로 remove_const 등과 같은 함수가 있습니다.
 */

#include <iostream>

/*
 * true_type 과 false_type은 단순히
 * 그 타입의 이름에 맞는 value를 가지는 struct 타입입니다.
 */

struct true_type
{
	enum _value_ { value = true };
};

struct false_type
{
	enum _value_ { value = false };
};

/// <summary>
/// remove_const 함수들은 다른 메타 함수와는 다르게
/// value가 아닌 타입을 내놓습니다.
/// </summary>
template <typename T>
struct remove_const
{
	typedef T type;
};

template <typename T>
struct remove_const<const T>
{
	typedef T type;
};

template <typename T1, typename T2>
struct is_same
{
	enum _value_ { value = false };
};

template <typename T>
struct is_same<T, T>
{
	enum _value_ { value = true };
};

template <typename T>
struct is_void : is_same<typename remove_const<T>::type, void>
{
};

template <typename T>
struct is_nullptr : is_same<typename remove_const<T>::type, nullptr_t>
{
};

/*
 * is_integral
 * 정수형 타입만이 공유하는 특성은 없기 때문에, 수동으로 특수화해주어야 합니다.
 *
 * const 한정자가 붙은 여부에 따라 정수형, 실수형의 여부가 달라지는 것은 아니기 때문에 이를 제거하고 검사합니다.
 * is_integral_base 가 만들어진 이유도 const 한정자를 제거하기 위함입니다.
 */

template <typename T>
struct is_integral_base : false_type
{
};

#define _IS_INTEGRAL_SPECIALIZATION_(_type) template <> \
											struct is_integral_base<_type> : true_type { }

_IS_INTEGRAL_SPECIALIZATION_(signed int);

_IS_INTEGRAL_SPECIALIZATION_(signed short);

_IS_INTEGRAL_SPECIALIZATION_(signed long);

_IS_INTEGRAL_SPECIALIZATION_(signed long long);

_IS_INTEGRAL_SPECIALIZATION_(unsigned int);

_IS_INTEGRAL_SPECIALIZATION_(unsigned short);

_IS_INTEGRAL_SPECIALIZATION_(unsigned long);

_IS_INTEGRAL_SPECIALIZATION_(unsigned long long);

_IS_INTEGRAL_SPECIALIZATION_(unsigned char);

_IS_INTEGRAL_SPECIALIZATION_(char16_t);

_IS_INTEGRAL_SPECIALIZATION_(char32_t);

_IS_INTEGRAL_SPECIALIZATION_(wchar_t);

template <typename T>
struct is_integral : is_integral_base<typename remove_const<T>::type>
{
};

/*
 * is_floating_point
 * is_integral과 마찬가지로, 실수형 타입이 공유하는 특성은 없기 때문에 수동으로 특수화해주어야 합니다.
 */

template <typename T>
struct is_floating_point_base : false_type
{
};

#define _IS_FLOATING_POINT_SPECIALIZATION_(_type)	template<> \
													struct is_floating_point_base<_type> : true_type {}

_IS_FLOATING_POINT_SPECIALIZATION_(float);

_IS_FLOATING_POINT_SPECIALIZATION_(double);

template <typename T>
struct is_floating_point : is_floating_point_base<typename remove_const<T>::type>
{
};

/*
 * Test Functions
 */

void ThisFunctionWillReturnVoid()
{
	return;
}

void TestIsSame()
{
	std::cout << "is_same<int, long>::value = " << is_same<int, long>::value << std::endl;
	std::cout << "is_same<int, float>::value = " << is_same<int, float>::value << std::endl;
	std::cout << "is_same<int, int>::value = " << is_same<int, int>::value << std::endl;
	std::cout << std::endl;
}

void TestIsVoid()
{
	std::cout << "is_void<int>::value = " << is_void<int>::value << std::endl;
	std::cout << "is_void<long>::value = " << is_void<long>::value << std::endl;
	std::cout << "is_void<void>::value = " << is_void<void>::value << std::endl;
	std::cout << "is_void<decltype(0)>::value = " << is_void<decltype(0)>::value << std::endl;
	std::cout << "is_void<decltype(ThisFunctionWillReturnVoid())>::value = " << is_void<decltype(ThisFunctionWillReturnVoid())>::value << std::endl;
	std::cout << std::endl;
}

void TestIsNullptr()
{
	std::cout << "is_nullptr<int*>::value = " << is_nullptr<int*>::value << std::endl;
	std::cout << "is_nullptr<void*>::value = " << is_nullptr<void*>::value << std::endl;
	std::cout << "is_nullptr<nullptr_t>::value = " << is_nullptr<nullptr_t>::value << std::endl;
	std::cout << "is_nullptr<decltype(nullptr)>::value = " << is_nullptr<decltype(nullptr)>::value << std::endl;
	std::cout << "is_nullptr<const nullptr_t>::value = " << is_nullptr<const nullptr_t>::value << std::endl;
	std::cout << "is_nullptr<const decltype(nullptr)>::value = " << is_nullptr<const decltype(nullptr)>::value << std::endl;
	std::cout << std::endl;
}

void TestIsIntegral()
{
	std::cout << "is_integral<int>::value = " << is_integral<int>::value << std::endl;
	std::cout << "is_integral<int*>::value = " << is_integral<int*>::value << std::endl;
	std::cout << "is_integral<float>::value = " << is_integral<float>::value << std::endl;
	std::cout << "is_integral<const unsigned long long>::value = " << is_integral<const unsigned long long>::value << std::endl;
	std::cout << "is_integral<decltype(15)>::value = " << is_integral<decltype(15)>::value << std::endl;
	std::cout << "is_integral<decltype(15.)>::value = " << is_integral<decltype(15.)>::value << std::endl;
	std::cout << "is_integral<decltype(15.f)>::value = " << is_integral<decltype(15.f)>::value << std::endl;
	std::cout << std::endl;
}

void TestIsFloatingPoint()
{
	std::cout << "is_floating_point<int>::value = " << is_floating_point<int>::value << std::endl;
	std::cout << "is_floating_point<double>::value = " << is_floating_point<double>::value << std::endl;
	std::cout << "is_floating_point<double*>::value = " << is_floating_point<double*>::value << std::endl;
	std::cout << "is_floating_point<const float>::value = " << is_floating_point<const float>::value << std::endl;
	std::cout << "is_floating_point<decltype(15)>::value = " << is_floating_point<decltype(15)>::value << std::endl;
	std::cout << "is_floating_point<decltype(15.)>::value = " << is_floating_point<decltype(15.)>::value << std::endl;
	std::cout << "is_floating_point<decltype(15.f)>::value = " << is_floating_point<decltype(15.f)>::value << std::endl;
	std::cout << std::endl;
}

int main()
{
	TestIsSame();
	TestIsVoid();
	TestIsNullptr();
	TestIsIntegral();
	TestIsFloatingPoint();

	return 0;
}
