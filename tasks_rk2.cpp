#include "tasks_rk2.h"
#include <cmath>

Node::Node() {
    parent = nullptr;
    name = 0;
}

Node::Node(int nameNode) {
    parent = nullptr;
    name = nameNode + 1;
}

Node::~Node() {
    std::destroy(listChilds.begin(), listChilds.end());
}

Graph::Graph() {
    head = nullptr;
}

Graph::Graph(int countNodes){
    head = new Node(countNodes);
}

Graph::~Graph() {
    delete head;
}

int Node::countNodes = 0;

int Graph::buildTreeBFS(int countNodes) {
    FIFO<Node*> st;
    head = new Node;
    st.AddEl(head);
    Node *buf;
    int count = countNodes;
    int count1 = 0;
    while(countNodes > 0) {
        st.GetEl(buf);
        for (int i = 0; i < countNodes; ++i) {
            Node *p = new Node(Node::countNodes++);
            st.AddEl(p);
            count1++;
            buf->listChilds.push_back(p);
            p->parent = buf;
        }
        if(count == count1) {
            countNodes--;
            count = count1*countNodes;
            count1 = 0;
        }
    }
    iter = head;
    discovered.resize(100);
    return Node::countNodes;
}

int Graph::Fact(int n){
    if(n < 2)
        return 1;
    else
        return n*Fact(n-1);
}

int Graph::buildTreeDFS(int countNodes){
    return -1;
}

void Graph::BFS() {
    FILE* pFile = fopen("bfs_res.txt", "w");
    FIFO<Node*> st;
    Node *iter1 = head;
    st.AddEl(iter1);
    Node *buf;
    while(!st.IsEmpty()) {
        st.GetEl(buf);
        fprintf(pFile, "%d%c", buf->name, '{');
        int i = 0;
        for (auto it: buf->listChilds) {
            if(i != buf->listChilds.size() - 1)
                fprintf(pFile, "%d%c", it->name, ',');
            else
                fprintf(pFile, "%d", it->name);
            st.AddEl(it);
            i++;
        }
        fprintf(pFile, "%s", "}\n");
    }
}

void Graph::DFS() {
    discovered[iter->name] = true;
    fprintf(Out, "%d%c", iter->name,' ');
    for(auto it : iter->listChilds){
        iter = it;
        if(!discovered[it->name]){
            DFS();
        }
    }
}

std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode){
    discovered[iter->name] = true;
    way.push_back(iter->name);
    for(auto it : iter->listChilds){
        iter = it;
        if(!discovered[it->name]){
            searchDFS(nameNode);
        }
        if(it->name != nameNode)
            way.pop_back();
    }
    return std::make_pair(true, way);
}

std::pair<bool, std::list<int>> Graph::searchBFS(int nameNode){
    FIFO<Node*> st;
    Node *iter1 = head;
    st.AddEl(iter1);
    Node *buf;
    while(!st.IsEmpty()) {
        st.GetEl(buf);
        if(buf->name == nameNode)
            break;
        for (auto it: buf->listChilds) {
            st.AddEl(it);
        }
    }
    std::vector<int> buffer;
    Node *p = buf;
    while(p->parent != nullptr) {
        buffer.push_back(p->parent->name);
        p = p->parent;
    }
    for(int i = buffer.size()-1; i > -1; i--){
        way.push_back(buffer[i]);
    }
    return std::make_pair(true, way);
}