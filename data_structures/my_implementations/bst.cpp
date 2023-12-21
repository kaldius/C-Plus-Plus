#include <iostream>

template <typename T>
class BinarySearchTree {
    private:
        struct BstNode {
            T value;
            std::unique_ptr<BstNode> left;
            std::unique_ptr<BstNode> right;

            BstNode(T val) {
                value = val;
                left = nullptr;
                right = nullptr;
            }
        };

        std::unique_ptr<BstNode> root;
        std::size_t size;

        bool insert(std::unique_ptr<BstNode>& node, T val) {
            if (node == nullptr) {
                node = std::make_unique<BstNode>(val);
                return true;
            }
            if (val < node->value) {
                return insert(node->left, val);
            } else if (val > node->value) {
                return insert(node->right, val);
            } else { 
                return false;
            }
            return true;
        }

        bool remove(std::unique_ptr<BstNode>& node, std::unique_ptr<BstNode>& parent, T val) {
            if (node == nullptr) {
                return false;
            }
            if (val == node->value) {
                if (node->left) {
                    // find max in left child, put it here, and delete it
                    T h;
                    findMax(node->left, h);
                    remove(node->left, node, h);
                    node->value = h;
                } else if (node->right) {
                    // find min in right child, put it here, and delete it
                    T l;
                    findMin(node->right, l);
                    remove(node->right, node, l);
                    node->value = l;
                } else {
                    if (!parent) {
                        node = nullptr;
                    } else if (node->value < parent->value) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                    return true;
                }
                return true;
            }
            if (val < node->value) {
                return remove(node->left, node, val);
            } else {
                return remove(node->right, node, val);
            }
            return false;
        }

        bool findMax(std::unique_ptr<BstNode>& node, T& output) {
            if (node == nullptr) {
                return false;
            }
            if (node->right) {
                // search right child
                return findMax(node->right, output);
            }
            output = node->value;
            return true;
        }

        bool findMin(std::unique_ptr<BstNode>& node, T& output) {
            if (node == nullptr) {
                return false;
            }
            if (node->left) {
                // search left child
                return findMax(node->left, output);
            }
            output = node->value;
            return true;
        }

        bool contains(std::unique_ptr<BstNode>& node, T val) {
            if (!node) {
                return false;
            }

            if (node->value == val) {
                return true;
            } else if (val < node->value) {
                return contains(node->left, val);
            } else {
                return contains(node->right, val);
            }
        }

        void inorderTraversal(std::function<void(T)> callback,
                               std::unique_ptr<BstNode>& node) const {
            if (!node) {
                return;
            }

            inorderTraversal(callback, node->left);
            callback(node->value);
            inorderTraversal(callback, node->right);
        }

        void preorderTraversal(std::function<void(T)> callback,
                                std::unique_ptr<BstNode>& node) const {
            if (!node) {
                return;
            }

            callback(node->value);
            preorderTraversal(callback, node->left);
            preorderTraversal(callback, node->right);
        }

        void postorderTraversal(std::function<void(T)> callback,
                               std::unique_ptr<BstNode>& node) const {
            if (!node) {
                return;
            }

            postorderTraversal(callback, node->left);
            postorderTraversal(callback, node->right);
            callback(node->value);
        }

    public:
        BinarySearchTree() {
            root = nullptr;
            size = 0;
        }

        bool insert(T val) {
            bool success = insert(root, val);
            if (success) {
                size++;
            }
            return success;
        }

        bool remove(T val) {
            std::unique_ptr<BstNode> parent = nullptr;
            bool success = remove(root, parent, val);
            if (success) {
                size--;
            }
            return success;
        }

        bool contains(T val) {
            return contains(root, val);
        }

        bool findMin(T& val) {
            return findMin(root, val);
        }

        bool findMax(T& val) {
            return findMax(root, val);
        }

        std::vector<T> asVectorInOrder() {
            std::vector<T> output = {};
            std::function<void(T)> callback = [&output](T val) { output.push_back(val); };
            inorderTraversal(callback, root);
            return output;
        }

        std::vector<T> asVectorPreOrder() {
            std::vector<T> output = {};
            std::function<void(T)> callback = [&output](T val) { output.push_back(val); };
            preorderTraversal(callback, root);
            return output;
        }

        std::vector<T> asVectorPostOrder() {
            std::vector<T> output = {};
            std::function<void(T)> callback = [&output](T val) { output.push_back(val); };
            postorderTraversal(callback, root);
            return output;
        }

        std::size_t getSize() {
            return size;
        }
};

template <typename T>
void printBst(BinarySearchTree<T>* bst) {
    auto vec = bst->asVectorInOrder();
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    BinarySearchTree<int>* bst = new BinarySearchTree<int>();
    bst->insert(1);
    bst->insert(6);
    bst->insert(3);
    bst->insert(10);
    printBst(bst);
    std::cout << std::endl;

    std::cout << "-----------removing 6----------" << std::endl;
    std::cout << "contains 6: " << bst->contains(6) << std::endl;
    bst->remove(6);
    std::cout << "inorder: ";
    printBst(bst);
    std::cout << "contains 6: " << bst->contains(6) << std::endl;
    std::cout << "size: " << bst->getSize() << std::endl;

    std::cout << "-----------removing 1----------" << std::endl;
    std::cout << "contains 1: " << bst->contains(1) << std::endl;
    bst->remove(1);
    std::cout << "inorder: ";
    printBst(bst);
    std::cout << "contains 1: " << bst->contains(1) << std::endl;
    std::cout << "size: " << bst->getSize() << std::endl;

    std::cout << "-----------removing 8----------" << std::endl;
    std::cout << "contains 8: " << bst->contains(8) << std::endl;
    bst->remove(8);
    std::cout << "inorder: ";
    printBst(bst);
    std::cout << "contains 8: " << bst->contains(8) << std::endl;
    std::cout << "size: " << bst->getSize() << std::endl;

}
