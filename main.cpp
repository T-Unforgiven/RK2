
#include "tasks_rk2.h"

void task_1(){
    Graph g;
    g.buildTreeBFS(3);
    g.BFS();
    g.DFS();
    g.searchBFS(3);
    g.searchDFS(13);
}

int main() {
    task_1();
    return 0;
}
