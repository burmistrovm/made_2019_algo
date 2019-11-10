/*
* 6_3. Выведите элементы в порядке post-order (снизу вверх)
*/
#include <vector>

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
    TreeNode* current_node = root;
    while (current_node){
        if (value > current_node->value) {
            current_node = current_node->right;
        }
        else
        {
            current_node = current_node->left;
        }
    }
}

int main()
{
    return 0;
};
