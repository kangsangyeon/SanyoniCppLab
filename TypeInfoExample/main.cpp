#include <iostream>
#include <typeindex>

class SomeClass
{
	char _a;
};

class A
{
	int _i;
};

class B
{
	char _c;
};

class C
{
	float _f;
};

int main()
{
	std::type_index _someClassTypeIndex = std::type_index(typeid(SomeClass));
	std::type_index _aTypeIndex = std::type_index(typeid(A));
	std::type_index _bTypeIndex = std::type_index(typeid(B));
	std::type_index _cTypeIndex = std::type_index(typeid(C));

	std::cout << "SomeClass type index: " << _someClassTypeIndex.hash_code() << ", " << _someClassTypeIndex.name()
		<< std::hash<const char*>()(_someClassTypeIndex.name()) << std::endl;
	std::cout << "a type index: " << _aTypeIndex.hash_code() << ", " << _aTypeIndex.name() << std::endl;
	std::cout << "b type index: " << _bTypeIndex.hash_code() << ", " << _bTypeIndex.name() << std::endl;
	std::cout << "c type index: " << _cTypeIndex.hash_code() << ", " << _cTypeIndex.name() << std::endl;

	return 0;
}
