#ifndef NEW_STACK_HPP
#define NEW_STACK_HPP

#include "../../node.hpp"
#include <iostream>
#include <stdexcept>  /// for std::invalid_argument

template <typename ValueType>
class NewStack {
    public: 
        using value_type = ValueType;

    private:
        std::shared_ptr<Node<value_type>> stackTop = nullptr;
        std::size_t size = 0;

        void ensureNotEmpty() const {
            if (isEmptyStack()) {
                throw std::invalid_argument("Stack is empty.");
            }
        }

    public:
        bool isEmptyStack() const {
            return size <= 0 && stackTop == nullptr;
        }

        std::vector<value_type> toVector() const {
            return push_all_to_vector(stackTop.get(), size);
        }


        void push(const value_type& item) {
            auto newNodePtr = std::make_shared<Node<value_type>>();
            newNodePtr->data = item;
            newNodePtr->next = stackTop;
            stackTop = newNodePtr;
            size++;
        }

        value_type top() const {
            ensureNotEmpty();
            return stackTop.get()->data;
        }

        void pop() {
            ensureNotEmpty();
            stackTop = stackTop->next;
            size--;
        }
        
        void clear() {
            stackTop = nullptr;
            size = 0;
        }

        void display() const {
            std::cout << "Top --> ";
            display_all(stackTop.get());
            std::cout << '\n';
            std::cout << "Size of stack: " << size << std::endl;
        }
};

#endif
