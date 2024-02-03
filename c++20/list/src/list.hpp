#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>
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
   public:
    Node<T>* m_head;

   public:
    List();
    ~List();

    template <typename U>
    List(const U& val)
        requires std::convertible_to<U, T>;

    template <typename U>
    List(const std::initializer_list<U> l)
        requires std::convertible_to<U, T>;

    List(const List<T>& l);

    template <typename U>
    List(const List<U>& l)
        requires(std::convertible_to<U, T> || std::same_as<U, T>);

    List& operator=(const List<T>& l);

    template <typename U>
    List& operator=(const List<U>& l)
        requires(std::convertible_to<U, T> || std::same_as<U, T>);

    List(List<T>&& l) noexcept;

    List& operator=(List<T>&& l) noexcept;

    void print() noexcept;

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
List<T>::List(const std::initializer_list<U> l)
    requires std::convertible_to<U, T>
{
    if (l.size() == 0) {
        m_head = nullptr;
        return;
    }
    Node<T>* m_head = new Node<T>(static_cast<T>(l[0]));
    Node<T>* tmp = m_head->next;
    for (int i = 1; i < l.size(); ++i) {
        tmp = new Node<T>(static_cast<T>(l[i]));
        tmp = tmp->next;
    }
}

template <typename T>
List<T>::List(const List<T>& l)
{
    std::cout << "Default copy constructor" << std::endl;
    if (l.m_head != nullptr) {
        this->m_head = new Node<T>(l.m_head->val);
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
template <typename U>
List<T>::List(const List<U>& l)
    requires(std::convertible_to<U, T> || std::same_as<U, T>)
{
    std::cout << "Non default copy constructor" << std::endl;
    if (l.m_head != nullptr) {
        this->m_head = new Node<T>(static_cast<T>(l.m_head->val));
    }
    Node<T>* tmp = this->m_head;
    Node<U>* tmp_l = l.m_head;
    while (tmp_l->next != nullptr) {
        tmp->next = new Node<T>(static_cast<T>(tmp_l->next->val));
        tmp = tmp->next;
        tmp_l = tmp_l->next;
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& l)
{
    std::cout << "Default assignment constructor" << std::endl;
    Node<T>* tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T>* _tmp = tmp->next;
        delete tmp;
        tmp = nullptr;
        tmp = _tmp;
    }
    return *this = List<T>(l);
}

template <typename T>
template <typename U>
List<T>& List<T>::operator=(const List<U>& l)
    requires(std::convertible_to<U, T> || std::same_as<U, T>)
{
    std::cout << "Non default assignment constructor" << std::endl;
    Node<T>* tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T>* _tmp = tmp->next;
        delete tmp;
        tmp = nullptr;
        tmp = _tmp;
    }
    return *this = List<T>(l);
}

template <typename T>
List<T>::List(List<T>&& l) noexcept
{
    std::cout << "Move constructor" << std::endl;
    this->m_head = l.m_head;
    l->m_head->next = nullptr;
    l->m_head = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& l) noexcept
{
    std::cout << "Move Assignment constructor" << std::endl;
    Node<T>* tmp = this->m_head;
    while (tmp != nullptr) {
        Node<T>* _tmp = tmp->next;
        delete tmp;
        tmp = _tmp;
    }
    this->m_head = l.m_head;
    l.m_head->next = nullptr;
    l.m_head = nullptr;
    return *this;
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
void List<T>::print() noexcept
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
    Node<T>* tmp = new Node<T>(static_cast<T>(val));
    tmp->next = m_head;
    m_head = tmp;
}

#endif
