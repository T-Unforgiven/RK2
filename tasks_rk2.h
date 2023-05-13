//
// Created by mrbru on 08.05.2023.
//

#ifndef RK2_TASKS_RK2_H
#define RK2_TASKS_RK2_H

#include <list>
#include <vector>
#include "Data.h"

struct Node {
    Node();
    Node(int nameNode);
    ~Node();

    Node* parent;
    std::list<Node*> listChilds;
    int name;
    bool WasHere;
    static int countNodes;
};

class Graph {
private :
    Node* head;
    Node* DFSearch(int nameNode);
    FILE* Out = fopen("dfs_res.txt", "w");
    Node *iter;
public :
    Graph();
    Graph(int countNodes);
    ~Graph();

    int buildTreeBFS(int countNodes);
    int buildTreeDFS(int countNodes);
    void BFS();
    void DFS();

    std::pair<bool, std::list<int>> searchDFS(int nameNode);
    std::pair<bool, std::list<int>> searchBFS(int nameNode);
};



#endif //RK2_TASKS_RK2_H
