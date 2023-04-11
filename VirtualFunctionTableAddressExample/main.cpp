#include <iostream>

class Parent
{
public:
	virtual void SayHello()
	{
		std::cout << "parent: hello" << std::endl;
	}
};

class Child : public Parent
{
public:
	void SayHello() override
	{
		std::cout << "child: hi" << std::endl;
	}
};

class ChildOfChild : public Child
{
};

int main()
{
	Parent* _parentInstance1 = new Parent();
	Parent* _parentInstance2 = new Parent();
	Parent* _parentInstance3 = new Parent();

	void* _parentInstance1VfTable = *(void**)(_parentInstance1);
	void* _parentInstance2VfTable = *(void**)(_parentInstance2);
	void* _parentInstance3VfTable = *(void**)(_parentInstance3);

	std::cout << "[parent 1] virtual function table address: " << _parentInstance1VfTable << std::endl;
	std::cout << "[parent 2] virtual function table address: " << _parentInstance2VfTable << std::endl;
	std::cout << "[parent 3] virtual function table address: " << _parentInstance3VfTable << std::endl;
	std::cout << std::endl;

	Parent* _childInstance1 = new Child();
	Parent* _childInstance2 = new Child();
	Parent* _childInstance3 = new Child();

	void* _childInstance1VfTable = *(void**)(_childInstance1);
	void* _childInstance2VfTable = *(void**)(_childInstance2);
	void* _childInstance3VfTable = *(void**)(_childInstance3);

	std::cout << "[child 1] virtual function table address: " << _childInstance1VfTable << std::endl;
	std::cout << "[child 2] virtual function table address: " << _childInstance2VfTable << std::endl;
	std::cout << "[child 3] virtual function table address: " << _childInstance3VfTable << std::endl;
	std::cout << std::endl;

	Parent* _childInParentInstance1 = new Child();
	Parent* _childInParentInstance2 = new Child();
	Parent* _childInParentInstance3 = new Child();

	void* _childInParentInstance1VfTable = *(void**)(_childInParentInstance1);
	void* _childInParentInstance2VfTable = *(void**)(_childInParentInstance2);
	void* _childInParentInstance3VfTable = *(void**)(_childInParentInstance3);

	std::cout << "[child in parent 1] virtual function table address: " << _childInParentInstance1VfTable << std::endl;
	std::cout << "[child in parent 2] virtual function table address: " << _childInParentInstance2VfTable << std::endl;
	std::cout << "[child in parent 3] virtual function table address: " << _childInParentInstance3VfTable << std::endl;
	std::cout << std::endl;

	Parent* _childOfChildInstance1 = new ChildOfChild();
	Parent* _childOfChildInstance2 = new ChildOfChild();
	Parent* _childOfChildInstance3 = new ChildOfChild();

	void* _childOfChildInstance1VfTable = *(void**)(_childOfChildInstance1);
	void* _childOfChildInstance2VfTable = *(void**)(_childOfChildInstance2);
	void* _childOfChildInstance3VfTable = *(void**)(_childOfChildInstance3);

	std::cout << "[child of child 1] virtual function table address: " << _childOfChildInstance1VfTable << std::endl;
	std::cout << "[child of child 2] virtual function table address: " << _childOfChildInstance2VfTable << std::endl;
	std::cout << "[child of child 3] virtual function table address: " << _childOfChildInstance3VfTable << std::endl;
	std::cout << std::endl;

	return 0;
}
