//
// Created by mrbru on 16.04.2023.
//

#ifndef RK2_DATA_H
#define RK2_DATA_H
template<typename T>
class IData{
protected:
    T *ar;
    int size;
    int DataLen;
public:
    IData(){
        size = 16;
        ar = new T[size];
        DataLen = 0;
    }
    ~IData(){
        delete[] ar;
    }
    virtual int AddEl(T element){
        if(DataLen == size)
            return -1;
        ar[DataLen++] = element;
        return 0;
    }
    virtual int GetEl(T& element){
        if(DataLen == 0)
            return -1;
        element = ar[--DataLen];
        return 0;
    }
};

template<typename T>
class FILO : public IData<T>{
};

template<typename T>
class FIFO : public IData<T>{
public:
    int GetEl(T& element) override{
        if(IData<T>::DataLen == 0)
            return -1;
        element =  IData<T>::ar[0];
        for (int i = 1; i <  IData<T>::DataLen; ++i) {
            std::swap( IData<T>::ar[i],  IData<T>::ar[i-1]);
        }
        IData<T>::DataLen--;
        return 0;
    }
};

template<typename T>
class RingedBuffer : IData<T>{
private:
    int begin;
    int end;
public:
    RingedBuffer(int FirstEl){
        begin = end = FirstEl;
    }
    int AddEl(T element) override{
        if(IData<T>::DataLen == IData<T>::size)
            return -1;
        IData<T>::ar[end] = element;
        IData<T>::DataLen++;
        end = (begin+IData<T>::DataLen)%IData<T>::size;
        return 0;
    }
    int GetEl(T& element) override{
        if(IData<T>::DataLen == 0)
            return -1;
        element = IData<T>::ar[begin++];
        begin = begin%IData<T>::size;
        IData<T>::DataLen--;
        return 0;
    }
};

template<typename T>
class LinkNodes{
public:
    LinkNodes<T> *next;
    LinkNodes<T> *prev;
    T data;
};

template<typename T>
class LinkedList : public LinkNodes<T>, IData<T>{
private:
    LinkNodes<T>* CreateNode(T element){
        LinkNodes<T>* l = new LinkNodes<T>;
        l->data = element;
        l->next = nullptr;
        l->prev = nullptr;
        IData<T>::DataLen++;
        return l;
    }
public:
    LinkNodes<T> *Head;
    bool IsEmpty(){
        if(IData<T>::DataLen == 0)
            return true;
        return false;
    }
    int AddEl(T element) override{
        if(IsEmpty()){
            Head = CreateNode(element);
            return 0;
        }
        LinkNodes<T>* p = Head;
        for (int i = 0; i < IData<T>::DataLen - 1; ++i) {
            p = p->next;
        }
        p->next = CreateNode(element);
        return 0;
    }
    int InsertEl(T element, int position){
        if (position < 0 || position > IData<T>::DataLen)
            return -1;
        LinkNodes<T>* p = Head;
        for (int i = 0; i < position - 1; ++i) {
            p = p->next;
        }
        LinkNodes<T>* l = p->next;
        p->next = CreateNode(element);
        p = p->next;
        p->next = l;
        return 0;
    }
    int DeleteNode(int position){
        if (position < 0 || position >= IData<T>::DataLen)
            return -1;
        LinkNodes<T>* p = Head;
        for (int i = 0; i < position - 1; ++i) {
            p = p->next;
        }
        LinkNodes<T>* l = p->next;
        p->next = l->next;
        IData<T>::DataLen--;
        delete l;
        return 0;
    }
    int DeleteList(){
        int a = IData<T>::DataLen;
        for (int i = 0; i < a; ++i) {
            LinkNodes<T>* p = Head;
            Head = Head->next;
            delete p;
            IData<T>::DataLen--;
        }
        return 0;
    }
};

template<typename T>
class DoubleLinkedList : public IData<T>, LinkNodes<T>{
private:
    LinkNodes<T>* CreateNode(T element){
        LinkNodes<T>* l = new LinkNodes<T>;
        l->data = element;
        l->next = nullptr;
        l->prev = nullptr;
        IData<T>::DataLen++;
        return l;
    }
public:
    LinkNodes<T> *Head;
    LinkNodes<T> *Tail;
    bool IsEmpty(){
        if(IData<T>::DataLen == 0)
            return true;
        return false;
    }
    int AddEl(T element) override{
        if(IsEmpty()){
            Head = Tail = CreateNode(element);
            return 0;
        }
        LinkNodes<T>* p = Head;
        for (int i = 0; i < IData<T>::DataLen - 1; ++i) {
            p = p->next;
        }
        p->next = CreateNode(element);
        p->next->prev = p;
        Tail = p->next;
        return 0;
    }
    int InsertEl(T element, int position){
        if (position < 0 || position > IData<T>::DataLen)
            return -1;
        LinkNodes<T>* p = Head;
        for (int i = 0; i < position - 1; ++i) {
            p = p->next;
        }
       p->next->prev = CreateNode(element);
        p->next->prev->next = p->next;
        p->next->prev->prev = p;
        p->next = p->next->prev;
        return 0;
    }
    int DeleteNode(int position){
        if (position < 0 || position >= IData<T>::DataLen)
            return -1;
        LinkNodes<T>* p = Head;
        for (int i = 0; i < position - 1; ++i) {
            p = p->next;
        }
        LinkNodes<T>* l = p->next;
        p->next = l->next;
        l->next->prev = p;
        IData<T>::DataLen--;
        delete l;
        return 0;
    }
    int DeleteList(){
        int a = IData<T>::DataLen;
        for (int i = 0; i < a; ++i) {
            LinkNodes<T>* p = Head;
            Head = Head->next;
            delete p;
            IData<T>::DataLen--;
        }
        return 0;
    }
};

#endif //RK2_DATA_H
