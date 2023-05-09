#include <iostream>
#include "tasks_rk2.h"

int main() {

    Graph g;
    g.buildTreeBFS(3);
    //g.searchBFS(15);
    for(auto it : g.searchBFS(8).second){
        std::cout << it << "   ";
    }
    return 0;
}
