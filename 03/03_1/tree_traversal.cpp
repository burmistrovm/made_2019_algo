/*
* 6_3. Выведите элементы в порядке post-order (снизу вверх)
*/
#include <vector>
#include <iostream>

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
    Binary_Tree(){};
    void insert(int value);
    std::vector<TreeNode*> post_order_traversal();
    ~Binary_Tree();
private:
    TreeNode* root = nullptr;
};

void Binary_Tree::insert(int value)
{
    bool stop_flag = false;
    TreeNode* current_node = root;
    if (!root)
    {
        root = new TreeNode(value);
        stop_flag = true;
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
                stop_flag = true;
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
                stop_flag = true;
                current_node->left = new TreeNode(value);
            }
        }
    }
}

std::vector<TreeNode*> Binary_Tree::post_order_traversal()
{
    std::vector<TreeNode*> res = std::vector<TreeNode*>();
    std::vector<TreeNode*> parents = std::vector<TreeNode*>();
    TreeNode* curr_node = root;
    TreeNode* last_node = nullptr;
    bool is_first = true;
    while ((parents.size() != 0) or is_first) {
        is_first = false;
        // если текущая нода существует, и мы ни разу не были
        // в ее левом поддереве, то движемся туда
        if ((curr_node != nullptr) and (curr_node != last_node))
        {
            parents.push_back(curr_node);
            curr_node = curr_node->left;
        }
        else
        {
            // в противном случае достаем из стэка родителя
            // и пробуем пройти в его правое поддерево
            // если ни разу там не были
            curr_node = parents.back();
            if ((curr_node->right != nullptr) & (curr_node->right != last_node))
            {
                curr_node = curr_node->right;
            } else
            {
                parents.pop_back();
                res.push_back(curr_node);
                last_node = curr_node;
            }
        }
    }
    return res;
}

Binary_Tree::~Binary_Tree()
{
    std::vector<TreeNode*> res = this->post_order_traversal();
    for (auto node:res)
    {
        delete node;
    }
}

int main()
{
    Binary_Tree tree = Binary_Tree();
    int num_nodes = 0;
    int value = 0;
    std::cin >> num_nodes;
    for (int i = 0; i < num_nodes; i++) {
        std::cin >> value;
        tree.insert(value);
    }
    std::vector<TreeNode*> res = tree.post_order_traversal();
    for (TreeNode* node:res)
    {
        std::cout << node->value << " ";
    }
    return 0;
};
