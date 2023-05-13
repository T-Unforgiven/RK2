//
// Created by mrbru on 16.04.2023.
//

#ifndef RK2_DATA_H
#define RK2_DATA_H

#include <utility>
#include <iostream>

template<typename T>
class IData{
protected:
    T *ar;
    int size;
    int DataLen;
public:
    IData(){
        size = 256;
        ar = new T[size];
        DataLen = 0;
    }
    ~IData(){
        delete[] ar;
    }
    virtual int AddEl(T element){
     return -2;
    }
    virtual int GetEl(T& element){
       return -2;
    }
    virtual bool IsEmpty(){
        return true;
    }

    virtual int InsertEl(T element, int position){
        return -2;
    }

    virtual int DeleteNode(int position){
        return -2;
    }

    virtual  int DeleteList(){
        return -2;
    }

    virtual int getSize(){
        return -2;
    }
};

template<typename T>
class FILO : public IData<T>{
public:
    int AddEl(T element) override{
        if(IData<T>::DataLen == IData<T>::size)
            return -1;
        IData<T>::ar[IData<T>::DataLen++] = element;
        return 0;
    }

    int GetEl(T& element) override{
        if( IData<T>::DataLen == 0)
            return -1;
        element =  IData<T>::ar[-- IData<T>::DataLen];
        return 0;
    }

    bool IsEmpty() override{
        return  IData<T>::DataLen == 0;
    }

    int getSize() override{
        return IData<T>::DataLen;
    }
};

template<typename T>
class FIFO : public IData<T>{
public:
    int AddEl(T element) override{
        if(IData<T>::DataLen == IData<T>::size)
            return -1;
        IData<T>::ar[IData<T>::DataLen++] = element;
        return 0;
    }

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

    bool IsEmpty() override{
        return  IData<T>::DataLen == 0;
    }

    int getSize() override{
        return IData<T>::DataLen;
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
        length++;
        return l;
    }
    int length = 0;
public:
    LinkNodes<T> *Head;
    bool IsEmpty() override{
        if(length == 0)
            return true;
        return false;
    }
    int AddEl(T element) override{
        if(IsEmpty()){
            Head = CreateNode(element);
            return 0;
        }
        LinkNodes<T>* p = Head;
        for (int i = 0; i < length - 1; ++i) {
            p = p->next;
        }
        p->next = CreateNode(element);
        return 0;
    }
    int InsertEl(T element, int position) override{
        if (position < 0 || position > length)
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
    int DeleteNode(int position) override{
        if (position < 0 || position >= length)
            return -1;
        LinkNodes<T>* p = Head;
        for (int i = 0; i < position - 1; ++i) {
            p = p->next;
        }
        LinkNodes<T>* l = p->next;
        p->next = l->next;
        length--;
        delete l;
        return 0;
    }
    int DeleteList() override{
        int a = length;
        for (int i = 0; i < a; ++i) {
            LinkNodes<T>* p = Head;
            Head = Head->next;
            delete p;
            length--;
        }
        return 0;
    }

    T& operator[](int i){
        LinkNodes<T>* p = Head;
        for (int j = 0; j < i; ++j) {
            p = p->next;
        }
        return p->data;
    }

    bool operator ==(LinkedList<T>& lst){
        if(length != lst.length)
            return false;
        int count = 0;
        LinkNodes<T>* p = Head;
        for (int i = 0; i < length; ++i) {
            if(p->data !=lst[i])
                count++;
            p = p->next;
        }
        if(count != 0)
            return false;
        return true;
    }

    LinkedList<T>& operator=(LinkedList<T>& lst){
        this->DeleteList();
        for (int i = 0; i < lst.length; ++i) {
            this->AddEl(lst[i]);
        }
        return *this;
    }

    void sort(){

    }

//    LinkNodes<T>* GetMin(){
//        int* ar = new int[this->length];
//        for (int i = 0; i < this->length; ++i) {
//            ar[i] = 0;
//        }
//        LinkNodes<T>* p = Head;
//        LinkNodes<T>* min = p;
//        int g = 0;
//        while(p!=nullptr){
//            if(p->data < min->data && ar[g] != 1) {
//                min = p;
//                ar[g] = 1;
//            }
//            p = p->next;
//            g++;
//        }
//        return min;
//    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, LinkedList<T>& lst){
    LinkNodes<T>* p = lst.Head;
    while(p != nullptr) {
        os << p->data << std::endl;
        p = p->next;
    }
    return os;
}

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
    bool IsEmpty() override{
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
    int InsertEl(T element, int position) override{
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
    int DeleteNode(int position) override{
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
    int DeleteList() override{
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
