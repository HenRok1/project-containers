#ifndef S21_LIST_S21_LIST_H_
#define S21_LIST_S21_LIST_H_

#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>
#include <valarray>

namespace s21 {

    template <typename T>
    struct Node {
        T *value_{};
        Node *next_{};
        Node *prev_{};
        Node() : value_(), next_(nullptr), prev_(nullptr) {}
        explicit Node(const T &value) : value_(value), next_(nullptr), prev_(nullptr) {}
        explicit Node(const T &&value) : value_(std::move(value)), next_(nullptr), prev_(nullprt) {}
    };

    template <typename T, typename Alloc = std::allocator<T>>
    class List {
        public:
            using value_type = T;
            using size_type = std::size_t;
            using reference = value_type &;
            using const_reference = const value_type &;
            using ValueTypeAlloc = Alloc;
        private:
            
    }
}

#endif // S21_LIST_S21_LIST_H_