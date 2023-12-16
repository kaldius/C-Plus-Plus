#include "../../node.hpp"
#include "../../stack.hpp"
#include <cassert>
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

void displayBoth(NewStack<int> stackA, stack<int> stackB) {
    std::cout << "Check that the below 2 are the same:\n1" << std::endl;
    stackA.display();
    std::cout << "2\n" << std::endl;
    stackB.display();
    std::cout << "----" << std::endl;
}

int main() {
    stack<int> oldStack;
    NewStack<int> newStack;

    newStack.push(10);
    newStack.push(20);
    newStack.push(30);
    oldStack.push(10);
    oldStack.push(20);
    oldStack.push(30);

    displayBoth(newStack, oldStack);

    newStack.pop();
    oldStack.pop();

    displayBoth(newStack, oldStack);

    newStack.pop();
    newStack.pop();
    oldStack.pop();
    oldStack.pop();

    std::string oldError;
    std::string newError;

    try {
        // should throw error
        newStack.pop();
    } catch (const std::invalid_argument& e) {
        newError = e.what();
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
    }

    try {
        // should throw error
        oldStack.pop();
    } catch (const std::invalid_argument& e) {
        oldError = e.what();
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
    }

    // std::cout << "oldError: " << oldError << "\nnewError: " << newError << std::endl;
    assert(oldError == newError);

    newStack.push(10);
    newStack.push(20);
    oldStack.push(10);
    oldStack.push(20);

    std::vector<int> expectedV = {20, 10};

    auto newV = newStack.toVector();
    auto oldV = oldStack.toVector();

    /*
    for (auto i : oldV) {
        std::cout << i;
    }
    std::cout << std::endl;
    */

    assert(expectedV == newV);
    assert(expectedV == oldV);

    assert(newStack.top() == 20);
    assert(newStack.top() == 20);
    assert(newStack.top() == 20);
    assert(oldStack.top() == 20);
    assert(oldStack.top() == 20);
    assert(oldStack.top() == 20);

    assert(!newStack.isEmptyStack());
    assert(!oldStack.isEmptyStack());
    newStack.clear();
    oldStack.clear();
    assert(newStack.isEmptyStack());
    assert(oldStack.isEmptyStack());

    return 0;
}

