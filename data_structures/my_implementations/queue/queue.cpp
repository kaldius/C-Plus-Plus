#include "../../node.hpp"
#include <iostream>
#include <cassert>
#include <stdexcept>  /// for std::invalid_argument

template <typename ValueType>
class NewQueue {
    private: 
        using node_type = Node<ValueType>;

    public:
        using value_type = ValueType;

        void display() const {
            std::cout << "Front --> ";
            display_all(queueFront.get());
            std::cout << '\n';
            std::cout << "Size of queue: " << size << '\n';
        }

        std::vector<value_type> toVector() const {
            return push_all_to_vector(queueFront.get());
        }

        bool isEmptyQueue() const {
            return queueFront == nullptr && size == 0;
        }

        // todo
        void enQueue(const value_type& item) {
            // create a new node
            auto newNodePtr = std::make_shared<node_type>();
            newNodePtr->data = item;
            newNodePtr->next = nullptr;
            if (isEmptyQueue()) {
                // make both queueFront and queueBack point to it
                queueFront = newNodePtr;
                queueBack = newNodePtr;
            } else {
                // make queueBack.next point to it
                // make queueBack point to it
                queueBack->next = newNodePtr;
                queueBack = newNodePtr;
            }
            size++;
        }

        value_type front() const {
            ensureNotEmpty();
            return queueFront->data;
        }

        void deQueue() {
            ensureNotEmpty();
            queueFront = queueFront->next;
            size--;
        }

        void clear() {
            queueFront = nullptr;
            queueBack = nullptr;
            size = 0;
        }

    private:
        std::shared_ptr<node_type> queueFront = {};
        std::shared_ptr<node_type> queueBack = {};
        std::size_t size = 0;

        void ensureNotEmpty() const {
            if (isEmptyQueue()) {
                throw std::invalid_argument("Queue is empty.");
            }
        }
};

void printGreen(const std::string& message) {
    // ANSI escape code for green text: \033[1;32m
    std::cout << "\033[1;32m" << message << "\033[0m" << std::endl;
}

int main() {
    // Test Case 1: Create an empty queue
    NewQueue<int> myQueue;
    assert(myQueue.isEmptyQueue());
    assert(myQueue.toVector().empty());

    // Test Case 2: Enqueue elements
    myQueue.enQueue(10);
    myQueue.enQueue(20);
    myQueue.enQueue(30);

    // Test Case 3: Display and check front
    myQueue.display();
    assert(!myQueue.isEmptyQueue());
    assert(myQueue.front() == 10);

    // Test Case 4: Dequeue
    myQueue.deQueue();
    assert(!myQueue.isEmptyQueue());
    assert(myQueue.front() == 20);

    // Test Case 5: Enqueue more elements
    myQueue.enQueue(40);
    myQueue.enQueue(50);

    // Test Case 6: Display and check size
    myQueue.display();
    assert(myQueue.toVector().size() == 4);

    // Test Case 7: Clear the queue
    myQueue.clear();
    assert(myQueue.isEmptyQueue());
    assert(myQueue.toVector().empty());

    // Additional Test Case: Enqueue after clearing
    myQueue.enQueue(60);
    assert(!myQueue.isEmptyQueue());
    assert(myQueue.front() == 60);

    printGreen("All test cases passed!\n");
    return 0;
}

