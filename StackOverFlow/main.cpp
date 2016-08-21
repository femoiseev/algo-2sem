#include <cassert>
#include <vector>

struct A {
    void* parent;
    template<typename T> A(T* p)
    {
        parent = new T(p);
    }
};

struct B
{
    A a;
    B() : a(new std::vector<int>()) {}
};

int main()
{
    B b1;
    B b2 = b1;
    assert(b1.a.parent != b2.a.parent);
    return 0;
}