#include "list.hpp"

int main()
{
    List<int> l1;
    l1.add(2);
    l1.add(4);
    l1.add(114);
    // List<int> l3;
    // l3 = l1;
    // l1.print();
    // l3.print();
    // List<float> l4;
    List<int> l4 = std::move(l1);
    l1.print();
    l4.print();
    List<float> l2 = l1;
    l1.add(5);
    l1.print();
    l2.print();
}
