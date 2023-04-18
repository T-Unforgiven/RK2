#include <iostream>
#include "Data.h"



int main() {
    LinkedList<char> lst;
    lst.AddEl('w');
    lst.AddEl('i');
    lst.AddEl('n');
    lst.InsertEl('e', 2);
    LinkNodes<char>* l = lst.Head;
    for (int i = 0; i < 4 ; ++i) {
        std::cout << l->data;
        l = l->next;
    }
    std::cout << std::endl;
    lst.DeleteNode(1);
    LinkNodes<char>* p = lst.Head;
    for (int i = 0; i < 3 ; ++i) {
        std::cout << p->data;
        p = p->next;
    }
    lst.DeleteList();
    if(lst.IsEmpty())
        std::cout << std::endl << "OK";
    return 0;
}
