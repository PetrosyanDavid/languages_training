#include "list.hpp"

int main()
{
    List<int> l1;
    l1.add(2);
    l1.add(4);
    List<int> l2(l1);
    l1.add(5);
    l1.print();
    l2.print();
}
