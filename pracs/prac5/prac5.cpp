#include <cassert>
#include <iostream>
#include <vector>
#include <stack>

enum NodeColor {
    RED,
    BLACK
};

template<typename T>
class RedBlackTreeNode {
public:
    T value;
    NodeColor color;
    RedBlackTreeNode* left;
    RedBlackTreeNode* right;
    RedBlackTreeNode* parent;

    // Конструктор узла дерева
    RedBlackTreeNode(T value, NodeColor color, RedBlackTreeNode<T>* left = nullptr, RedBlackTreeNode<T>* right = nullptr,
                     RedBlackTreeNode<T>* parent = nullptr): value(value), color(color), left(left), right(right),
                                                             parent(parent) {};

    // Возвращает указатель на дедушку текущего узла
    RedBlackTreeNode* grandparent() {
        assert(parent != nullptr);

        return parent->parent;
    }

    // Возвращает указатель на дядю текущего узла
    RedBlackTreeNode* uncle() {
        assert(grandparent() != nullptr);
        if (grandparent()->right == parent)
            return grandparent()->left;
        else
            return grandparent()->right;
    }

    // Проверяет, находится ли узел слева от родителя
    bool isLeft() {
        return parent->left == this;
    }

    // Проверяет, находится ли узел справа от родителя
    bool isRight() {
        return parent->right == this;
    }

    // Симметричный обход дерева
    void inOrderTraversal() {
        if (left != nullptr)
            left->inOrderTraversal();
        std::cout << value << " ";
        if (right != nullptr)
            right->inOrderTraversal();
    }

    // Прямой обход дерева
    void preOrderTraversal() {
        std::cout << value << " ";
        if (left != nullptr)
            left->inOrderTraversal();
        if (right != nullptr)
            right->inOrderTraversal();
    }

    // Вычисляет среднее значение значений всех узлов в дереве
    float mean() {
        std::vector<RedBlackTreeNode<T>*> stack = {this};
        T sum = 0;
        T count = 0;

        while (!stack.empty()) {
            RedBlackTreeNode<T>* node = stack[stack.size()-1];
            stack.pop_back();
            if (node->left != nullptr)
                stack.push_back(node->left);
            sum += node->value;
            count += 1;
            if (node->right != nullptr)
                stack.push_back(node->right);
        }

        return float(sum)/count;
    }
};

template<typename T>
class RedBlackTree {
private:
    RedBlackTreeNode<T>* root;

public:
    // Конструктор дерева
    RedBlackTree(): root(nullptr) {}

    // Вставляет новый узел в дерево и балансирует его
    void insert(T value) {
        if (root == nullptr) {
            root = new RedBlackTreeNode(value, BLACK);
            return;
        }

        // Вставка нового узла
        RedBlackTreeNode<T> *cur = root;
        RedBlackTreeNode<T> *z = nullptr;
        while (z == nullptr) {
            if (value == cur->value) {
                return;
            } else if (value > cur->value) {
                if (cur->right != nullptr) {
                    cur = cur->right;
                } else {
                    cur->right = new RedBlackTreeNode<T>(value, RED, nullptr, nullptr, cur);
                    z = cur->right;
                }
            } else { // value < cur->value
                if (cur->left != nullptr) {
                    cur = cur->left;
                } else {
                    cur->left = new RedBlackTreeNode<T>(value, RED, nullptr, nullptr, cur);
                    z = cur->left;
                }
            }
        }

        // Балансировка дерева
        if (z->parent == nullptr || z->grandparent() == nullptr || z->uncle() == nullptr)
            return;

        if (z->uncle()->color == RED) {
            z->parent->color = BLACK;
            z->grandparent()->color = RED;
            z->uncle()->color = BLACK;
        } else if (z->uncle()->color == BLACK) {
            if (z->isLeft() && z->parent->isRight()) { // triangle
                rightRotate(z->parent);
            } else if (z->isRight() && z->parent->isLeft()) { // triangle
                leftRotate(z->parent);
            } else if (z->isLeft() && z->parent->isLeft()) { // line
                z->parent->color = BLACK;
                z->grandparent()->color = RED;
                rightRotate(z->grandparent());
            } else if (z->isRight() && z->parent->isRight()) { // line
                z->parent->color = BLACK;
                z->grandparent()->color = RED;
                leftRotate(z->grandparent());
            }
        }
    }

    // Симметричный обход дерева
    void inOrderTraversal() {
        if (root == nullptr)
            return;

        root->inOrderTraversal();
    }

    // Прямой обход дерева
    void preOrderTraversal() {
        if (root == nullptr)
            return;

        root->preOrderTraversal();
    }

    // Возвращает среднее арифметическое всех узлов в дереве
    float mean() {
        if (root == nullptr)
            return 0;

        return root->mean();
    }

    // Находит длину пути до указанного узла
    int findPathLength(T value) {
        if (!root) {
            return -1;
        }

        std::stack<std::pair<RedBlackTreeNode<T>*, int>> nodeStack = {};
        nodeStack.push({root, 0});

        while (!nodeStack.empty()) {
            RedBlackTreeNode<T>* node = nodeStack.top().first;
            int pathLength = nodeStack.top().second;
            nodeStack.pop();

            if (node->value == value) {
                return pathLength;
            }

            if (node->left != nullptr)
                nodeStack.push({node->left, pathLength + 1});
            if (node->right != nullptr)
                nodeStack.push({node->right, pathLength + 1});
        }

        return -1;
    }

private:
    // Поворот узла влево
    void leftRotate(RedBlackTreeNode<T>* x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x->parent != nullptr) {
            if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Поворот узла вправо
    void rightRotate(RedBlackTreeNode<T>* x) {
        auto y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (y->parent == nullptr)
            root = y;
        else if (x->parent == nullptr) {
            if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }
};

int main() {
    auto tree = RedBlackTree<char>();

    auto elements = {'t', 'b', 'x', 'f', 'd', 'k', 'z', 'z', 'y', 'r', 'a'};

    // Вставка символов в дерево
    for (auto ch: elements) {
        tree.insert(ch);
    }

    // Прямой обход (pre order) дерева
    std::cout << "Прямой обход (pre order):" << std::endl;
    tree.preOrderTraversal();

    std::cout << "\n";
    // Симметричный обход (in order) дерева
    std::cout << "Симметричный обход (in order):" << std::endl;
    tree.inOrderTraversal();

    std::cout << "\n";
    // Вывод среднего значения всех узлов в дереве
    std::cout << "Среднее арифметическое всех узлов: " << tree.mean() << std::endl;

    std::cout << "\n";
    // Вывод длины пути до каждого узла из вставленного набора
    for (auto ch: elements) {
        std::cout << "Длина пути до '"<< ch << "': " << tree.findPathLength(ch) << std::endl;
    }
}
