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

/*
 * value_type는 템플릿 매개변수로 bool형을 받습니다.
 * 이처럼 템플릿 매개변수로 타입 뿐만 아니라 bool형과 int형을 받을 수 있는데,
 * 이런 매개변수를 비형식 템플릿 매개변수(Non-type template argument)라고 합니다.
 *
 * 비형식 템플릿 매개변수를 받아 수학적 연산도 가능합니다.
 *
 * value_type<false>는 false_type을 상속받고, value_type<true>는 true_type을 상속받습니다.
 * 매개변수로 건네진 bool형의 값에 따라 내부에 정의된 enum의 값을 결정짓기 위해 이렇게 상속받습니다.
 *
 * https://caniro.tistory.com/144
 * https://en.cppreference.com/w/cpp/language/template_parameters
 */

template <bool _value = false>
struct value_type : false_type
{
};

template <>
struct value_type<true> : true_type
{
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
 * is_arithmetic, is_fundamental, is_compound
 * is_arithmetic 메타 함수는 매개변수로 받은 타입이 정수형 또는 실수형일 때 true를 반환하는 함수입니다.
 * is_fundamental 메타 함수는 is_arithmetic 에 nullptr_t를 검사하는 로직이 추가된 함수입니다.
 * is_compound 메타 함수는 정수형, 실수형, nullptr_t, void 가 아닌 모든 타입에 대해 true를 반환하는 함수입니다.
 *
 * 앞서 구현한 is_integral과 is_floating_point를 상속하여 매우 간단하게 구현할 수 있습니다.
 */

template <typename T>
struct is_arithmetic : value_type<is_integral<T>::value | is_floating_point<T>::value>
{
};

template <typename T>
struct is_fundamental : value_type<is_arithmetic<T>::value | is_nullptr<T>::value | is_void<T>::value>
{
};

template <typename T>
struct is_compound : value_type<!is_fundamental<T>::value>
{
};

/*
 * is_pointer, is_reference, is_const, is_volatile, is_signed, is_unsigned
 */

template <typename T>
struct is_pointer_base : false_type
{
};

template <typename T>
struct is_pointer_base<T*> : true_type
{
};

template <typename T>
struct is_pointer : is_pointer_base<typename remove_const<T>::type>
{
};

template <typename T>
struct is_reference_base : false_type
{
};

template <typename T>
struct is_reference_base<T&> : true_type
{
};

template <typename T>
struct is_reference_base<T&&> : true_type
{
};

template <typename T>
struct is_reference : is_reference_base<typename remove_const<T>::type>
{
};

template <typename T>
struct is_const : false_type
{
};

template <typename T>
struct is_const<const T> : true_type
{
};

template <typename T>
struct is_volatile : false_type
{
};

template <typename T>
struct is_volatile<volatile T> : true_type
{
};

template <typename T, bool _is_arithmethic = is_arithmetic<T>::value>
struct is_signed_base : value_type<T(-1) < T(0)>
{
};

template <typename T>
struct is_signed_base<T, false> : false_type
{
};

template <typename T>
struct is_signed : is_signed_base<T>
{
};

/*
 * is_array
 * 정적 배열인지 판별하는 메타 함수입니다.
 * 크기가 지정되지 않은 배열 타입과 크기가 정해진 배열 타입 모두 판별이 가능합니다.
 * 크기가 미리 정해진 배열 타입인 경우, 그 크기를 얻어올 수 있습니다.
 * (미리 정해진 크기의 배열 타입은 컴파일 타임에 결정되는 크기이기 때문입니다.)
 *
 * *동적 배열은 포인터이기 때문에 확인이 불가능합니다.
 */

template <typename T>
struct is_array : false_type
{
};

template <typename T>
struct is_array<T[]> : true_type
{
};

template <typename T, size_t ArrSize>
struct is_array<T[ArrSize]> : true_type
{
};

/*
 * Test Functions
 */

class CustomClass
{
};

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

void TestIsArithmetic()
{
	std::cout << "is_arithmetic<int>::value = " << is_arithmetic<int>::value << std::endl;
	std::cout << "is_arithmetic<float>::value = " << is_arithmetic<float>::value << std::endl;
	std::cout << "is_arithmetic<int*>::value = " << is_arithmetic<int*>::value << std::endl;
	std::cout << "is_arithmetic<const int>::value = " << is_arithmetic<const int>::value << std::endl;
	std::cout << "is_arithmetic<int&>::value = " << is_arithmetic<int&>::value << std::endl;
	std::cout << "is_arithmetic<nullptr_t>::value = " << is_arithmetic<nullptr_t>::value << std::endl;
	std::cout << std::endl;
}

void TestIsFundamental()
{
	std::cout << "is_fundamental<int>::value = " << is_fundamental<int>::value << std::endl;
	std::cout << "is_fundamental<float>::value = " << is_fundamental<float>::value << std::endl;
	std::cout << "is_fundamental<nullptr_t>::value = " << is_fundamental<nullptr_t>::value << std::endl;
	std::cout << "is_fundamental<decltype(nullptr)>::value = " << is_fundamental<decltype(nullptr)>::value << std::endl;
	std::cout << "is_fundamental<CustomClass>::value = " << is_fundamental<CustomClass>::value << std::endl;
	std::cout << std::endl;
}

void TestIsCompound()
{
	std::cout << "is_compound<int>::value = " << is_compound<int>::value << std::endl;
	std::cout << "is_compound<float>::value = " << is_compound<float>::value << std::endl;
	std::cout << "is_compound<nullptr_t>::value = " << is_compound<nullptr_t>::value << std::endl;
	std::cout << "is_compound<decltype(nullptr)>::value = " << is_compound<decltype(nullptr)>::value << std::endl;
	std::cout << "is_compound<CustomClass>::value = " << is_compound<CustomClass>::value << std::endl;
	std::cout << std::endl;

	std::cout << is_signed_base<CustomClass>::value << std::endl;
}

void TestIsArray()
{
	std::cout << "is_array<int>::value = " << is_array<int>::value << std::endl;
	std::cout << "is_array<int[]>::value = " << is_array<int[]>::value << std::endl;
	std::cout << "is_array<int[20]>::value = " << is_array<int[20]>::value << std::endl;
	std::cout << "is_array<CustomClass>::value = " << is_array<CustomClass>::value << std::endl;
	std::cout << "is_array<CustomClass[]>::value = " << is_array<CustomClass[]>::value << std::endl;
}

int main()
{
	TestIsSame();
	TestIsVoid();
	TestIsNullptr();
	TestIsIntegral();
	TestIsFloatingPoint();
	TestIsArithmetic();
	TestIsFundamental();
	TestIsCompound();
	TestIsArray();

	return 0;
}
