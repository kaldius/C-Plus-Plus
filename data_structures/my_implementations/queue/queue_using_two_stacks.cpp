#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>  /// for std::invalid_argument

namespace {
    /**
     * @brief Queue data structure. Stores elements in FIFO
     * (first-in-first-out) manner.
     * @tparam ValueType datatype to store in the queue
     */
    template <typename ValueType>
    class MyQueue {
        public:
            using value_type = ValueType;

        private:
            std::stack<value_type> s1, s2;

            void cleanup();

        public:
            /**
             * Constructor for queue.
             */
            MyQueue() = default;

            /**
             * Pushes x to the back of queue.
             */
            void push(const value_type&);

            /**
             * Removes an element from the front of the queue.
             */
            value_type pop();

            /**
             * Returns first element, without removing it.
             */
            value_type peek();

            /**
             * Returns whether the queue is empty.
             */
            bool empty() const;
    };

    template <typename ValueType>
    void MyQueue<ValueType>::cleanup() {
        if (!s1.empty()) { return; }
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    template <typename ValueType>
    void MyQueue<ValueType>::push(const ValueType& x) {
        s2.push(x);
    }

    template <typename ValueType>
    ValueType MyQueue<ValueType>::pop() {
        if (empty()) {
            throw std::invalid_argument("Queue is empty.");
        }
        cleanup();
        auto tmp = s1.top();
        s1.pop();
        return tmp;
    }

    template <typename ValueType>
    ValueType MyQueue<ValueType>::peek() {
        if (empty()) {
            throw std::invalid_argument("Queue is empty.");
        }
        cleanup();
        return s1.top();
    }

    template <typename ValueType>
    bool MyQueue<ValueType>::empty() const {
        return s1.empty() && s2.empty();
    }

    
}  // namespace

/**
 * Testing function
 */
void queue_test() {
    MyQueue<int> que;
    std::cout << "Test #1\n";
    que.push(2);
    que.push(5);
    que.push(0);
    assert(que.peek() == 2);
    assert(que.pop() == 2);
    assert(que.peek() == 5);
    assert(que.pop() == 5);
    assert(que.peek() == 0);
    assert(que.pop() == 0);
    assert(que.empty() == true);
    std::cout << "PASSED\n";

    std::cout << "Test #2\n";
    que.push(-1);
    assert(que.empty() == false);
    assert(que.peek() == -1);
    assert(que.pop() == -1);
    std::cout << "PASSED\n";

    MyQueue<double> que2;
    std::cout << "Test #3\n";
    que2.push(2.31223);
    que2.push(3.1415926);
    que2.push(2.92);

    assert(que2.peek() == 2.31223);
    assert(que2.pop() == 2.31223);
    assert(que2.peek() == 3.1415926);
    assert(que2.pop() == 3.1415926);
    assert(que2.peek() == 2.92);
    assert(que2.pop() == 2.92);
    std::cout << "PASSED\n";
}

/**
 * Main function, calls testing function
 */
int main() {
    queue_test();
    return 0;
}
