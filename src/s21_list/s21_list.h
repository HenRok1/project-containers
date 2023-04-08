#ifndef S21_LIST_S21_LIST_H_
#define S21_LIST_S21_LIST_H_

#include <initializer_list>
#include <iterator>
#include <limits>

/* Контейнер List - обычно представлен в виде двусвязанного списка */

namespace s21 {
    template <typename T/*, typename Alloc = std::allocator<T>*/>
    class List {
        public:
            /* value_type - тип переменной */
            using value_type = T;

            /* size_type - размер контейнера */
            using size_type = std::size_t;
            
            /* reference - тип ссылки на элемент */
            using reference = value_type &;

            /* const_reference - тип константной ссылки на элемент */
            using const_reference = const value_type &;

            /* iterator - класс для итератора */
            using iterator = ListIterator;

            /* const_iterator - класс для константного итератора */

            using const_iterator = ListIteratorConst;

            /* node_type - класс для узла  списка */
            using node_type = Node;

            List() : head_(new node_type{}), size_(0U) {}


        private:
            struct Node;
            struct ListIterator;
            struct ConstListIterator;

            struct Node {
                value_type value_;
                node_type *next_;
                node_type *prev_;

                Node() noexcept : value_(0), next_(nullptr), prev_(nullptr) {}
                explicit Node(const_reference  &value) noexcept : value_(value), next_(nullptr), prev_(nullptr) {}
                explicit Node(value_type &&value) noexcept : value_(std::move(value)), next_(nullptr), prev_(nullptr) {}


            };
/*
            struct ListIterator {
                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = list::value_type;
                using pointer = value_type *;
                using reference = value_type &;

                ListIterator() = delete;

                explicit ListIterator(node_type *node) noexcept : node_(node) {}

                reference operator*() const noexcept {
                    return node_->value_;
                }
                iterator &operator++() noexcept {
                    node_ = node_->next_;
                    return *this;
                }
                
                iterator operator++(int) noexcept {
                    iterator tmp{node_};
                    ++(*this);
                    return tmp;
                }

                iterator operator--() noexcept {
                    node_ = node_->prev_;
                    return *this;
                }

                iterator operator--(int) noexcept {
                    iterator temp{node_};
                    --(*this);
                    return temp;
                }

                bool operator==(const iterator &other) const noexcept {
                    return node_== other.node_;
                }

                bool operator!=(const iterator &other) const noexcept {
                    return node_ != other.node_;
                }

                node_type *node_;
            };
            */
            
    };
}

#endif // S21_LIST_S21_LIST_H_