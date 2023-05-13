#include "tasks_rk2.h"
#include <cmath>

Node::Node() {
    WasHere = false;
    parent = nullptr;
    name = 0;
}

Node::Node(int nameNode) {
    WasHere = false;
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
    return Node::countNodes;
}

int Graph::buildTreeDFS(int countNodes){
    head = new Node;
    for (int i = 0; i < countNodes; ++i) {
        FILO<Node*> st;
        st.AddEl(head);
        int n = countNodes;
        Node *buf;
        while (!st.IsEmpty()) {
            st.GetEl(buf);
            Node *l = buf;
            if (n <= l->listChilds.size()) {
                n++;
                continue;
            }
            while (n > l->listChilds.size()) {
                Node *p = new Node(Node::countNodes++);
                l->listChilds.push_back(p);
                p->parent = l;
                st.AddEl(p);
                n--;
                l = p;
            }
        }
    }
    iter = head;
    return Node::countNodes;
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
    iter->WasHere = true;
    fprintf(Out, "%d%c", iter->name,' ');
    for(auto it : iter->listChilds){
        iter = it;
        if(!iter->WasHere){
            DFS();
        }
    }
}

std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode){
    Node *target = DFSearch(nameNode);
    std::list<int> way;
    if(target == nullptr)
        return std::make_pair(false, way);
    while(target!=nullptr){
        way.push_back(target->name);
        target = target->parent;
    }
    std::list<int> trueWay;
    way.reverse();
    return std::make_pair(true, way);
}

std::pair<bool, std::list<int>> Graph::searchBFS(int nameNode){
    bool foundIt = false;
    FIFO<Node*> st;
    Node *iter1 = head;
    st.AddEl(iter1);
    Node *buf;
    std::list<int> way;
    while(!st.IsEmpty()) {
        st.GetEl(buf);
        if(buf->name == nameNode) {
            foundIt = true;
            break;
        }
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
    return std::make_pair(foundIt, way);
}

Node* Graph::DFSearch(int nameNode) {
    FILO<Node*> stack;
    stack.AddEl(head);
    Node* buf;
    while(!stack.IsEmpty()){
        stack.GetEl(buf);
        if(buf->WasHere)
            continue;
        buf->WasHere = true;
        if(buf->name == nameNode) {
            return buf;
        }
        for(auto it : buf->listChilds){
            if(!it->WasHere)
                stack.AddEl(it);
        }
    }
    return nullptr;
}