#include <cassert>   /// for assert
#include <iostream>
#include <stdexcept>  /// for std::invalid_argument

template <typename T>
class Queue {
    private:
    struct LLNode {
        T value;
        std::shared_ptr<LLNode> next;
    };

    std::shared_ptr<LLNode> front;
    std::shared_ptr<LLNode> rear;
    std::size_t size;
    std::size_t max_size;

    public:
    Queue(std::size_t max_size) {
        if (max_size < 1) {
            throw std::invalid_argument("Size of queue must be at least 1.");
        }
        
        front = std::make_shared<LLNode>();
        front->next = nullptr;

        std::shared_ptr<LLNode> curr = front;
        int i = 1;
        while (i++ < max_size) {
            curr->next = std::make_shared<LLNode>();
            curr->next->next = nullptr;

            curr = curr->next;
        }
        
        curr->next = front;
        size = 0;
        this->max_size = max_size;
        rear = curr;
    }
    
    void enqueue(const T& val) {
        if (isFull()) {
            throw std::invalid_argument("Queue is full.");
        }
        rear->next->value = val;
        rear = rear->next;
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::invalid_argument("Queue is empty.");
        }
        T output = peek();
        front = front->next;
        size--;
        return output;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::invalid_argument("Queue is empty.");
        }
        return front->value;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == max_size;
    }

    std::size_t getSize() const {
        return size;
    }

    void clear() {
        front = rear->next;
        size = 0;
    }

    std::vector<T> toVector() const {
        std::vector<T> vec;
        std::shared_ptr<LLNode> curr = front;
        int i = 0;
        while (i++ < size) {
            vec.push_back(curr->value);
            curr = curr->next;
        }
        return vec;
    }
};

template <typename T>
void testConstructedQueueIsEmpty() {
    const Queue<T> curQueue(5);
    assert(curQueue.isEmpty());
}

void testEnqueue() {
    Queue<int> curQueue(5);
    curQueue.enqueue(10);
    assert(curQueue.toVector() == std::vector<int>({10}));
    curQueue.enqueue(20);
    assert(curQueue.toVector() == std::vector<int>({10, 20}));
    curQueue.enqueue(30);
    curQueue.enqueue(40);
    assert(curQueue.toVector() == std::vector<int>({10, 20, 30, 40}));
}

void testDequeue() {
    Queue<int> curQueue(5);
    curQueue.enqueue(10);
    curQueue.enqueue(20);
    curQueue.enqueue(30);

    curQueue.dequeue();
    assert(curQueue.toVector() == std::vector<int>({20, 30}));

    curQueue.dequeue();
    assert(curQueue.toVector() == std::vector<int>({30}));

    curQueue.dequeue();
    assert(curQueue.isEmpty());
}

void testPeek() {
    Queue<int> curQueue(5);
    curQueue.enqueue(10);
    assert(curQueue.peek() == 10);
    curQueue.enqueue(20);
    assert(curQueue.peek() == 10);
}

void testQueueAfterClearIsEmpty() {
    Queue<int> curQueue(5);
    curQueue.enqueue(10);
    curQueue.enqueue(20);
    curQueue.enqueue(30);
    curQueue.clear();
    assert(curQueue.isEmpty());
}

void testFrontThrowsAnInvalidArgumentWhenqueueEmpty() {
    const Queue<int> curQueue(5);
    bool wasException = false;
    try {
        curQueue.peek();
    } catch (const std::invalid_argument&) {
        wasException = true;
    }
    assert(wasException);
}

void testDeQueueThrowsAnInvalidArgumentWhenqueueEmpty() {
    Queue<int> curQueue(5);
    bool wasException = false;
    try {
        curQueue.dequeue();
    } catch (const std::invalid_argument&) {
        wasException = true;
    }
    assert(wasException);
}

int main() {
    testConstructedQueueIsEmpty<int>();
    testConstructedQueueIsEmpty<double>();
    testConstructedQueueIsEmpty<std::vector<long double>>();

    testEnqueue();
    testDequeue();

    testQueueAfterClearIsEmpty();

    testFrontThrowsAnInvalidArgumentWhenqueueEmpty();
    testDeQueueThrowsAnInvalidArgumentWhenqueueEmpty();

    std::cout << "All tests pass!\n";
    return 0;
}
