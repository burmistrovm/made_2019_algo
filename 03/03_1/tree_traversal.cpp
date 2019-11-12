/*
* 6_3. Выведите элементы в порядке post-order (снизу вверх)
*/
#include <vector>
#include <iostream>
#include <docobjectservice.h>

struct TreeNode
{
    explicit TreeNode(int _value) : value(_value) {}

    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class Binary_Tree
{
public:
    void insert(int value);
    void post_order_traversal();
private:
    TreeNode* root = nullptr;

};

void Binary_Tree::insert(int value)
{
    bool stop_flag = False;
    TreeNode* current_node = root;
    if (!root)
    {
        root = new TreeNode(value);
        stop_flag = True;
    }
    while (!stop_flag)
    {
        if (value > current_node->value)
        {
            if (current_node->right)
            {
                current_node = current_node->right;
            } else
            {
                stop_flag = True;
                current_node->right = new TreeNode(value);
            }
        }
        else
        {
            if (current_node->left)
            {
                current_node = current_node->left;
            } else
            {
                stop_flag = True;
                current_node->left = new TreeNode(value);
            }
        }
    }
}

void Binary_Tree::post_order_traversal()
{
    std::vector<TreeNode*> parents = std::vector<TreeNode*>();
    TreeNode* curr_node = root;
    parents.push_back(root);
    while (parents.size() != 0) {
        // на каждой итерации от текущей ноды движемся влево до конца
        while (curr_node)
        {
            if (curr_node->left) {
                parents.push_back(curr_node->left);
            }
            curr_node = curr_node->left;
        }
        // после прохода влево до конца выводим всех предков без правых
        // дочерних веток
        curr_node = parents.back();

        while ((parents.size() != 0) and (curr_node->right == nullptr))
        {
            std::cout << curr_node->value;
            parents.pop_back();
            curr_node = parents.back();
        }
        // для правых веток повторяем итерацию
        curr_node = curr_node->right;
        parents.push_back(curr_node);
    }
}

int main()
{
    std::vector<int>vec = std::vector<int>{1, 2, 3};
    Binary_Tree tree = Binary_Tree();
    for (int i = 0; i < 3; i++) {
        tree.insert(vec[i]);
    }
    tree.post_order_traversal();
    return 0;
};
