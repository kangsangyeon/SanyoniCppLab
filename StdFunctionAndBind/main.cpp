#include <functional>
#include <iostream>

class SomeClass
{
public:
	int SayFloat(float _value)
	{
		m_Value = 10;

		std::cout << "SomeClass::SayFloat: " << _value << std::endl;
		return 3;
	}

	int SayVar(int _i, char _c, float _f)
	{
		std::cout << "SomeClass::SayVar: " << _i << " " << _c << " " << _f << std::endl;
		return 3;
	}

	int m_Value;
};

int GlobalFunction(char _c)
{
	std::cout << "GlobalFunction: " << _c << std::endl;
	return 1;
}

int main()
{
	std::function<int(int)> SomeLambda = [](int _value)-> int
	{
		std::cout << "SomeLambda: " << _value << std::endl;
		return 2;
	};

	// std::function에 전역 변수를 대입할 수 있습니다.
	std::cout << "<global function assign to std::function> " << std::endl;
	std::function<int(char)> _globalFunction = GlobalFunction;
	std::cout << _globalFunction('a') << std::endl;
	std::cout << std::endl;

	// std::function에 람다 함수를 대입할 수 있습니다.
	std::cout << "<lambda function assign to std::function> " << std::endl;
	std::function<int(char)> _lambdaFunction = SomeLambda;
	std::cout << _lambdaFunction(10) << std::endl;
	std::cout << std::endl;

	// 전역 변수를 바인드할 수 있습니다.
	std::cout << "<bind global function> " << std::endl;
	std::function<int(void)> _bindGlobalFunction = std::bind(GlobalFunction, 'a');
	std::cout << _bindGlobalFunction() << std::endl;
	std::cout << std::endl;

	// 람다 함수를 바인드할 수 있습니다.
	std::cout << "<bind lambda function> " << std::endl;
	std::function<int(void)> _bindLambda = std::bind(SomeLambda, 222);
	std::cout << _bindLambda() << std::endl;
	std::cout << std::endl;

	// 멤버 변수를 바인드할 수 있습니다.
	// 이 때, 언바운드 함수를 호출하듯 두 번째 매개변수로 타입에 맞는 인스턴스의 pointer를 건네주어야 합니다.
	std::cout << "<bind member function> " << std::endl;
	SomeClass _instance;
	std::function<int(void)> _bindMemberFunction = std::bind(&SomeClass::SayFloat, &_instance, 90.f);
	std::cout << _bindMemberFunction() << std::endl;
	std::cout << std::endl;

	const int _num = 1;
	char _char = 'a';

	// bind할 때 모든 매개변수를 bind하지 않고도 placeholder를 사용하여 일단 미뤄둔 뒤
	// 호출할 때 매개변수를 건네줄 수도 있습니다.
	std::cout << "<bind member function2> " << std::endl;
	std::function<int(float)> _bindMemberFunction2 = std::bind(&SomeClass::SayVar, &_instance, _num, _char, std::placeholders::_1);
	_char = 'b';
	// SomeClass::SayVar: 1 a 10
	// 즉, bind한 이후에 바뀐 _char값은 반영되지 않습니다.
	std::cout << _bindMemberFunction2(10.f) << std::endl;

	return 0;
}
