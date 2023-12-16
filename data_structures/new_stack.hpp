#include <iostream>
#include <stdexcept>  /// for std::invalid_argument

template <typename ValueType>
class NewStack {
    public: 
        using value_type = ValueType;

    private:
        std::vector<value_type> _v;
        std::size_t size = 0;

        void ensureNotEmpty() const {
            if (isEmptyStack()) {
                throw std::invalid_argument("Stack is empty.");
            }
        }

    public:
        bool isEmptyStack() const {
            return size <= 0;
        }

        std::vector<value_type> toVector() const {
            std::vector<value_type> clonedVector = {_v.rbegin(), _v.rend()};
            return clonedVector;
        }


        void push(const value_type& item) {
            _v.push_back(item);
            size++;
        }

        value_type top() const {
            return _v.back();
        }

        void pop() {
            ensureNotEmpty();
            size--;
            _v.pop_back();
        }
        
        void clear() {
            std::vector<value_type> emptyVector;
            _v = emptyVector;
            size = 0;
        }

        void display() const {
            std::cout << "Top --> ";
            for (int i = size - 1; i >= 0; i--) {
                std::cout << _v[i] << " ";
            }
            std::cout << '\n';
            std::cout << "Size of stack: " << size << std::endl;
        }
};
