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

	// std::function�� ���� ������ ������ �� �ֽ��ϴ�.
	std::cout << "<global function assign to std::function> " << std::endl;
	std::function<int(char)> _globalFunction = GlobalFunction;
	std::cout << _globalFunction('a') << std::endl;
	std::cout << std::endl;

	// std::function�� ���� �Լ��� ������ �� �ֽ��ϴ�.
	std::cout << "<lambda function assign to std::function> " << std::endl;
	std::function<int(char)> _lambdaFunction = SomeLambda;
	std::cout << _lambdaFunction(10) << std::endl;
	std::cout << std::endl;

	// ���� ������ ���ε��� �� �ֽ��ϴ�.
	std::cout << "<bind global function> " << std::endl;
	std::function<int(void)> _bindGlobalFunction = std::bind(GlobalFunction, 'a');
	std::cout << _bindGlobalFunction() << std::endl;
	std::cout << std::endl;

	// ���� �Լ��� ���ε��� �� �ֽ��ϴ�.
	std::cout << "<bind lambda function> " << std::endl;
	std::function<int(void)> _bindLambda = std::bind(SomeLambda, 222);
	std::cout << _bindLambda() << std::endl;
	std::cout << std::endl;

	// ��� ������ ���ε��� �� �ֽ��ϴ�.
	// �� ��, ��ٿ�� �Լ��� ȣ���ϵ� �� ��° �Ű������� Ÿ�Կ� �´� �ν��Ͻ��� pointer�� �ǳ��־�� �մϴ�.
	std::cout << "<bind member function> " << std::endl;
	SomeClass _instance;
	std::function<int(void)> _bindMemberFunction = std::bind(&SomeClass::SayFloat, &_instance, 90.f);
	std::cout << _bindMemberFunction() << std::endl;
	std::cout << std::endl;

	const int _num = 1;
	char _char = 'a';

	// bind�� �� ��� �Ű������� bind���� �ʰ� placeholder�� ����Ͽ� �ϴ� �̷�� ��
	// ȣ���� �� �Ű������� �ǳ��� ���� �ֽ��ϴ�.
	std::cout << "<bind member function2> " << std::endl;
	std::function<int(float)> _bindMemberFunction2 = std::bind(&SomeClass::SayVar, &_instance, _num, _char, std::placeholders::_1);
	_char = 'b';
	// SomeClass::SayVar: 1 a 10
	// ��, bind�� ���Ŀ� �ٲ� _char���� �ݿ����� �ʽ��ϴ�.
	std::cout << _bindMemberFunction2(10.f) << std::endl;

	return 0;
}
