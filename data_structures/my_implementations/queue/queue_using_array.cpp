/**
 * @file
 * @brief Implementation of Linear [Queue using array]
 * (https://www.geeksforgeeks.org/array-implementation-of-queue-simple/).
 * @details
 * The Linear Queue is a data structure used for holding a sequence of
 * values, which can be added to the end line (enqueue), removed from
 * head of line (dequeue) and displayed.
 * ### Algorithm
 * Values can be added by increasing the `rear` variable by 1 (which points to
 * the end of the array), then assigning new value to `rear`'s element of the
 * array.
 *
 * Values can be removed by increasing the `front` variable by 1 (which points
 * to the first of the array), so it cannot reached any more.
 *
 * @author [Pooja](https://github.com/pooja-git11)
 * @author [Farbod Ahmadian](https://github.com/farbodahm)
 */
#include <array>     /// for std::array
#include <iostream>  /// for io operations
#include <stdexcept>

constexpr uint16_t max_size{3};  ///< Maximum size of the queue

/**
 * @namespace data_structures
 * @brief Algorithms with data structures
 */
namespace data_structures {

    /**
     * @namespace queue_using_array
     * @brief Functions for [Queue using Array]
     * (https://www.geeksforgeeks.org/array-implementation-of-queue-simple/)
     * implementation.
     */
    namespace queue_using_array {

        /**
         * @brief Queue_Array class containing the main data and also index of head and
         * tail of the array.
         */
        class Queue_Array {
            public:
                void enqueue(const int16_t&);  ///< Add element to the first of the queue
                int dequeue();                 ///< Delete element from back of the queue
                void display() const;          ///< Show all saved data
            private:
                int8_t front{0};                      ///< Index of head of the array
                int8_t rear{0};                       ///< Index of tail of the array
                std::array<int16_t, max_size> arr{};  ///< All stored data
                int nextIndex(int16_t) const;
                bool isFullQueue() const;
                bool isEmptyQueue() const;
        };

        void Queue_Array::enqueue(const int16_t& item) {
            // check that array is not full
            if (isFullQueue()) {
                throw std::invalid_argument("Queue is full.");
            }
            arr[rear] = item;
            rear = nextIndex(rear);
        }

        int Queue_Array::dequeue() {
            int16_t res = arr[front];
            front = nextIndex(front);
            return res;
        }

        void Queue_Array::display() const {
            if (isEmptyQueue()) {
                std::cout << "\nQueue is empty";
            } else {
                int16_t i = front;
                while (i != rear) {
                    std::cout << arr[i] << " ";
                    i = nextIndex(i);
                }
                std::cout << std::endl;
            }
        }

        int Queue_Array::nextIndex(int16_t idx) const {
            return (idx + 1) % max_size;
        }

        bool Queue_Array::isFullQueue() const {
            return nextIndex(rear) == front;
        }

        bool Queue_Array::isEmptyQueue() const {
            return rear == front;
        }
    }  // namespace queue_using_array
}  // namespace data_structures

/**
 * @brief Main function
 * @details
 * Allows the user to add and delete values from the queue.
 * Also allows user to display values in the queue.
 * @returns 0 on exit
 */
int main() {
    int op{0}, data{0};
    data_structures::queue_using_array::Queue_Array ob;

    std::cout << "\n1. enqueue(Insertion) ";
    std::cout << "\n2. dequeue(Deletion)";
    std::cout << "\n3. Display";
    std::cout << "\n4. Exit";
    while (true) {
        std::cout << "\nEnter your choice ";
        std::cin >> op;
        if (op == 1) {
            std::cout << "Enter data  ";
            std::cin >> data;
            try {
                ob.enqueue(data);
            } catch (const std::invalid_argument& e) {
                std::cout << e.what() << "\nData will not be enqueued" << std::endl;
            }
        } else if (op == 2) {
            data = ob.dequeue();
            std::cout << "\ndequeue element is:\t" << data;
        } else if (op == 3) {
            ob.display();
        } else if (op == 4) {
            exit(0);
        } else {
            std::cout << "\nWrong choice ";
        }
    }

    return 0;
}
