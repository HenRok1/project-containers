#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <list>

namespace s21 {
    template <typename T, typename Constainer = std::list<T>>
    class Stack {
        /* Поля и конструкторы */
        public:
            using value_type = T;
            using size_type = size_t;
            using reference = T &;
            using const_reference = const T &;
        
            /* Дефолтный конструктор */
            Stack() noexcept : container_{} {};

            /* Конструктор, который на вход получает список элементов */
            Stack(std::initializer_list<value_type> const &items) : container_{items} {}
            
            /* Конструктор копирования - копируются все элементы*/
            Stack(const stack &rhs) : container_{rhs.container_} {}

            /* Конструктор перемещения - перемещаются все элементы */
            Stack(stack &&rhs) : container_{std::move(rhs.container_)} {}

            /* Диструктор */
            ~Stack() noexcept : default;

            /* Оператор копирования */
            Stack* operator=(const stack &other) {
                container_ = rhs.container_;
                returh *this
            }
            /* Оператор перемещения */
            Stack* operator=(stack&&other) {
                container_ = std::move(rhs.container_);
                return *this;
            }
        /* Методы Stack*/
        public:
            /* top - вывод указателя верхнего элемента Stack */
            reference top() noexcept {
                return container_.back();
            }

            /* const_top - вывод const указателя верхнего элемента Stack */
            const_reference const_top() const noexcept {
                return container_.back();
            }
            /* empty - проверка, не пустой ли Stack*/
            bool empty() const noexcept {
                return container_.empty();
            }

            /* size - вывод количества элементов в Stack */
            size_type size() const noexcept {
                return container_.size();
            }

            /*push - добавление элемента в вершину Stack */
            void push(const value_type& value) {
                container_.push_back(value);
            }

            /*push - добавление элемента в вершину Stack */
            void push(value_type&& value) {
                container_.push_back(std::move(value));
            }

            /*pop - удаление элемента, находящийся в вершине Stack*/
            void pop() noexcept {
                container_.pop_back();
            }

            /*swap - изменений позиций двух элементов между собою*/
            void swap(stack& other) noexcept
                std::swap(container_, other.container_);

            /*нихуа непонятно что это*/
            template <typename... Args>
            decltype(auto) emplace(Args&&... args) {
                return container.emplace_back(std::forward<Args>(args)...);
            }

        private:
            Container container_;

    };
} // namespace s21

#endif // S21_STACK_H_ 