#include <iostream>
#include <vector>

class A
{
public:
    static int count;

    A()
    {
        ++count;
    }
};

int A::count = 0;

int main()
{
    // 요소가 없는 벡터에 resize(n)을 실시하면,
    // 기본값으로 채워집니다.
    std::cout << "요소가 없는 벡터에 resize(n)을 실시합니다." << std::endl;
    std::vector<int> a;
    a.resize(100);
    for (int i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << ", ";
    }

    std::cout << "\n\n";

    // 요소가 n개 이하인 벡터에 resize(n)을 실시하면
    // size 이후에 요소를 생성합니다.
    std::cout << "요소가 n개 이하인 벡터에 resize(n)을 실시합니다." << std::endl;
    std::vector<int> b;
    for (int i = 0; i < 50; ++i)
        b.push_back(i);

    b.resize(100);
    for (int i = 0; i < b.size(); ++i)
        std::cout << b[i] << ", ";

    std::cout << "\n\n";

    // 요소가 n개 이상인 벡터에 resize(n)을 실시하면
    // size 이후의 요소들을 삭제합니다.
    std::cout << "요소가 n개 이상인 벡터에 resize(n)을 실시합니다." << std::endl;
    std::vector<int> c;
    for (int i = 0; i < 200; ++i)
        c.push_back(i);

    c.resize(100);
    for (int i = 0; i < c.size(); ++i)
        std::cout << c[i] << ", ";

    std::cout << "\n\n";

    // 요소가 n개인 벡터에 resize(n)을 실시하면
    std::cout << "요소가 n개인 벡터에 resize(n)을 실시합니다." << std::endl;
    std::vector<int> d;
    for (int i = 0; i < 100; ++i)
        d.push_back(i);

    d.resize(100);
    for (int i = 0; i < d.size(); ++i)
        std::cout << d[i] << ", ";

    std::cout << "\n\n";

    // 클래스 타입 벡터에 resize를 실시하면
    // 요소들이 생성되며 요소들마다 생성자가 호출됩니다.
    std::cout << "클래스 타입을 가지는 벡터에 resize를 실시합니다." << std::endl;
    std::vector<A> e;
    e.resize(100);
    std::cout << "creation count: " << A::count;

    std::cout << "\n\n";

    return 0;
}
