#include <cassert>
#include <iostream>

// Include the queue header
#include "../../queue.hpp"

void printGreen(const std::string& message) {
    // ANSI escape code for green text: \033[1;32m
    std::cout << "\033[1;32m" << message << "\033[0m" << std::endl;
}

int main() {
    // Test Case 1: Create an empty queue
    queue<int> myQueue;
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

