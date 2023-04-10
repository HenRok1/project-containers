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

            /* Конструктор по умолчанию - создает пустой список*/
            List() : head_(new node_type{}), size_(0U) {}

            /* Конструктор, который создается список с длиной */
            explicit List(size_type n) : List() {
                while (n > 0) {
                    push_back(value_type{});
                    n--;
                }
            }

            /* Конструктор списка инициализаторов, создает список, который проинициализировался с помощью initializer_list */
            List(std::initializer_list<value_type> const &items) : List() {
                for (auto item : items) {
                    push_back(item);
                }
            }

            /* Конструктор копирования */
            List(const List& other) : List() {
                for (auto elem : other) {
                    push_back(elem);
                }
            }

            /* Конструктор перемещения */
            List(List &&other) : List() {
                splice(begin(), other); // нужно написать функцию, для перемещения
            }

            /* Оператор присваивания копированием - переиспольуем память, которая уже выделена */

            List &operator=(const List &other) {
                if (this != &other) {
                    iterator this_begin = begin();
                    iterator this_end = end();
                    const_iterator other_begin = other.begin();
                    const_iterator other_end = other.end();

                    /* 
                        Сначала заполняем уже существующие элементы в текущем списке, 
                        пока они не кончатся, либо пока не кончатся элементы в other
                    */

                    while (this_begin != this_end && other_begin != other_end) {
                        *this_begin = *other_begin;
                        ++this_begin;
                        ++other_begin;
                    }

                    /* Если в текущем элементе остались элементы, то удаляем их */

                    while (this_begin != this_end) {
                        iterator tmp = this_begin;
                        ++this_begin;
                        erase(tmp);
                    }

                    /* Если в other остались элементы, то пушим их в текущий список */

                    while (other_begin != other_end) {
                        push_back(*other_begin);
                        ++other_begin;
                    }
                }
                return *this;
            }
            
            /* Оператор присваивания перемещением */
            List &operator=(List &&other) {
                if (this != &other) {
                    clear();
                    splice(begin(), other); //реализовать функцию 
                }
                return *this;
            }

            /* Диструктор */
            ~List() noexcept {
                clear();
                delete head_;

                head_ = nullptr;
            }

            /* Доступ к первому элементу */
            reference front() noexcept {
                return *begin();
            }

            /* Доступ к первому элементу в константном контейнере */
            const_reference front() const noexcept {
                return *begin();
            }
            
            /* Доступ к последнему элементу */
            reference back() noexcept {
                return *std::prev(end());
            }
            
            /* Доступ к последнему элементу в константном контейнере */
            const_reference back() const noexcept {
                return *std::prev(end());
            }

            /* Возвращает итератор на начало контейнера */
            iterator begin() noexcept {
                return iterator{head_->next_};
            }

            /* Возвращает итератор на начало константного контейнера */
            const_iterator begin() const noexcept {
                return const_iterator{head_->next_};
            }

            /* Возвращает итератор на конец контейнера */
            iterator end() noexcept {
                return iterator{head_};
            }

            /* Возвращает итератор на конце константного контейнера */
            const_iterator end() const noexcept {
                return const_iterator{head_};
            }

            /* Проверка на пустой контейнер */
            bool empty() const noexcept {
                return size_ == 0;
            }

            /* Возвращает количество элементов в константном контейнере */
            size_type size() const noexcept {
                return size_;
            }

            /* max_size() сделать */

            /* Удаляет содержимое контейнера(все элементы) */
            void clear() noexcept {
                while (size_ > 0) {
                    erase(begin());
                }
            }

            /* insert() сделать*/

            void erase(iterator pos) noexcept {
                if (pos != end()) {
                    pos.node_->UnAttach();
                    delete pos.node_;
                    --size_;
                }
            }

            /* Добавляет элемент в конце списка */
            void push_back(const_reference value) {
                insert(end(), value);
            }

            /* Удаляет последний элемент списка */
            void pop_back() noexcept {
                erase(--end());
            }

            /* Добавляет элемент в начало списка */
            void push_front(const_reference value) {
                insert(begin(), value);
            }

            /* Удаляет первый элемент списка */
            void pop_front() noexcept {
                erase(begin());
            }

            /* обменивает содержимое двух списков */
            void swap(List &other) noexcept {
                if (this != &other) {
                    std::swap(head_, other.head_);
                    std::swap(size_, other.size_);
                }
            }

            /* merge() сделать */

            /* splice() сделать */

            /* reverse() сделать */

            /* unique() сделать */

            /* Сортирует элементы списка в пордяке возрастания */
            void sort() {
                quick_sort(begin(), --end(), size_);
            }

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