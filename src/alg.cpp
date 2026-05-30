// Copyright 2022 NNTU-CS
#include  <vector>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

void collectPermutations(Node* node, std::vector<char>* path,
                         std::vector<std::vector<char>>* res) {
    if (!node) return;

    if (node->val != '*') {
        path->push_back(node->val);
    }

    if (node->children.empty()) {
        if (node->val != '*') {
            res->push_back(*path);
        }
    } else {
        for (size_t i = 0; i < node->children.size(); ++i) {
            collectPermutations(node->children[i], path, res);
        }
    }

    if (node->val != '*') {
        path->pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collectPermutations(tree.getRoot(), &path, &result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> all = getAllPerms(tree);
    int limit = static_cast<int>(all.size());
    if (num <= 0 || num > limit) {
        return std::vector<char>();
    }
    return all[num - 1];
}

int calculateFactorial(int n) {
    int total = 1;
    while (n > 1) {
        total *= n;
        n--;
    }
    return total;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> path;
    Node* curr = tree.getRoot();

    if (!curr || curr->children.empty()) {
        return path;
    }

    int idx = num - 1;
    int size = static_cast<int>(curr->children.size());
    int total = calculateFactorial(size);

    if (idx < 0 || idx >= total) {
        return std::vector<char>();
    }

    while (!curr->children.empty()) {
        int branches = static_cast<int>(curr->children.size());
        int step = total / branches;

        int select = idx / step;
        curr = curr->children[select];

        path.push_back(curr->val);

        idx %= step;
        total = step;
    }

    return path;
}
