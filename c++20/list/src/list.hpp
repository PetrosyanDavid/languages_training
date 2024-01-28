#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T>
class Node
{
   public:
    T val;
    Node<T>* next;

   public:
    Node() : val(0), next(nullptr){};
    Node(T v) : val(v), next(nullptr){};
};

template <typename T>
class List
{
   private:
    Node<T>* m_head;

   public:
    List();
    ~List();
    List(const T& val);
    List(const List<T>& l);
    List& operator=(const List<T>& l);
    List(const List<T>&& l) noexcept;
    List& operator=(const List<T>&& l) noexcept;
    void print();
    void add(T val);
};

template <typename T>
List<T>::List() : m_head(new Node<T>(T()))
{
}

template <typename T>
List<T>::List(const T& val) : m_head(new Node<T>(val))
{
}

template <typename T>
List<T>::List(const List<T>& l)
{
    this->m_head = new Node<T>;
    if (l.m_head != nullptr) {
        this->m_head->val = l.m_head->val;
    }
    Node<T>* tmp = this->m_head;
    Node<T>* tmp_l = l.m_head;
    while (tmp_l->next != nullptr) {
        tmp->next = new Node<T>(tmp_l->next->val);
        tmp = tmp->next;
        tmp_l = tmp_l->next;
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& l)
{
    Node<T> tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T> _tmp = tmp->next;
        delete tmp;
        tmp = _tmp;
    }
    return *this = List<T>(l);
}

template <typename T>
List<T>::List(const List<T>&& l) noexcept
{
    this->m_head = l.m_head;
    l->m_head->next = nullptr;
    l->m_head = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>&& l) noexcept
{
    Node<T> tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T> _tmp = tmp->next;
        delete tmp;
        tmp = _tmp;
    }
    this->m_head = l->m_head;
    l->m_head->next = nullptr;
    l->m_head = nullptr;
}

template <typename T>
List<T>::~List()
{
    Node<T>* tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T>* _tmp = tmp->next;
        delete tmp;
        tmp = _tmp;
    }
    this->m_head = nullptr;
}

template <typename T>
void List<T>::print()
{
    Node<T>* tmp = this->m_head;
    while (tmp != nullptr) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

template <typename T>
void List<T>::add(T val)
{
    Node<T>* tmp = new Node(val);
    tmp->next = m_head;
    m_head = tmp;
}

#endif
