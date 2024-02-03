#include "list.hpp"

int main()
{
    List<int> l1;
    l1.add(2);
    l1.add(4);
    List<float> l3;
    l3 = l1;
    List<float> l2 = l1;
    l1.add(5);
    l1.print();
    l2.print();
}
