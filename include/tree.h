// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct Node {
    char val;
    std::vector<Node*> children;

    explicit Node(char c) : val(c) {}
};

class PMTree {
 private:
    Node* root;

    void buildTree(Node* curr, std::vector<char> items) {
        if (items.empty()) return;

        for (size_t i = 0; i < items.size(); ++i) {
            Node* child = new Node(items[i]);
            curr->children.push_back(child);

            std::vector<char> next_items = items;
            next_items.erase(next_items.begin() + i);

            buildTree(child, next_items);
        }
    }

    void clearTree(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            clearTree(child);
        }
        delete node;
    }

 public:
    explicit PMTree(std::vector<char> in) {
        for (size_t i = 0; i < in.size(); ++i) {
            size_t min_idx = i;
            for (size_t j = i + 1; j < in.size(); ++j) {
                if (in[j] < in[min_idx]) {
                    min_idx = j;
                }
            }
            char temp = in[i];
            in[i] = in[min_idx];
            in[min_idx] = temp;
        }
        root = new Node('*');
        buildTree(root, in);
    }

    ~PMTree() {
        clearTree(root);
    }

    Node* getRoot() const {
        return root;
    }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
