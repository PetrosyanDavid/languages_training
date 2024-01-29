#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <type_traits>

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
   public:
    Node<T>* m_head;

   public:
    List();
    ~List();

    template <typename U>
    List(const U& val)
        requires std::convertible_to<U, T>;

    template <typename U>
    List(const List<U>& l)
        requires(std::convertible_to<U, T> || std::same_as<U, T>);

    template <typename U>
    List& operator=(const List<U>& l)
        requires std::convertible_to<U, T>;

    template <typename U>
    List(const List<U>&& l) noexcept
        requires std::convertible_to<U, T>;

    template <typename U>
    List& operator=(const List<U>&& l) noexcept
        requires std::convertible_to<U, T>;

    void print();

    template <typename U>
    void add(U val)
        requires std::convertible_to<U, T>;
};

template <typename T>
List<T>::List() : m_head(nullptr)
{
}

template <typename T>
template <typename U>
List<T>::List(const U& val)
    requires std::convertible_to<U, T>
    : m_head(new Node<T>(val))
{
}

template <typename T>
template <typename U>
List<T>::List(const List<U>& l)
    requires(std::convertible_to<U, T> || std::same_as<U, T>)
{
    std::cout << "Copy constructor" << std::endl;
    if (l.m_head != nullptr) {
        this->m_head = new Node<T>(l.m_head->val);
    }
    Node<T>* tmp = this->m_head;
    Node<U>* tmp_l = l.m_head;
    while (tmp_l->next != nullptr) {
        tmp->next = new Node<T>(tmp_l->next->val);
        tmp = tmp->next;
        tmp_l = tmp_l->next;
    }
}

template <typename T>
template <typename U>
List<T>& List<T>::operator=(const List<U>& l)
    requires std::convertible_to<U, T>
{
    std::cout << "Assignment constructor" << std::endl;
    Node<T> tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T> _tmp = tmp->next;
        delete tmp;
        tmp = nullptr;
        tmp = _tmp;
    }
    return *this = List<T>(l);
}

template <typename T>
template <typename U>
List<T>::List(const List<U>&& l) noexcept
    requires std::convertible_to<U, T>
{
    std::cout << "Move constructor" << std::endl;
    this->m_head = l.m_head;
    l->m_head->next = nullptr;
    l->m_head = nullptr;
}

template <typename T>
template <typename U>
List<T>& List<T>::operator=(const List<U>&& l) noexcept
    requires std::convertible_to<U, T>
{
    std::cout << "Move Assignment constructor" << std::endl;
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
    std::cout << "Destructor" << std::endl;
    Node<T>* tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T>* _tmp = tmp->next;
        delete tmp;
        tmp = nullptr;
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
template <typename U>
void List<T>::add(U val)
    requires std::convertible_to<U, T>
{
    Node<T>* tmp = new Node(val);
    tmp->next = m_head;
    m_head = tmp;
}

#endif
