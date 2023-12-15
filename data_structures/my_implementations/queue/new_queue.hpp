#ifndef NEW_QUEUE_HPP
#define NEW_QUEUE_HPP

#include "../../node.hpp"
#include <iostream>
#include <stdexcept>  /// for std::invalid_argument

/*
* display()
* toVector()
* ensureNotEmpty()
* isEmptyQueue()
* enQueue() {
* front()
* deQueue()
* clear()
* queueFront
* queueRear
* size
*/

template <typename ValueType>
class NewQueue {
    public:
        using value_type = ValueType;
        using node_type = Node<value_type>;

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

#endif
