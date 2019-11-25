#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

struct BtNode
{
    BtNode *left, *right;
    char data;

    BtNode()
    {
        left = nullptr;
        right = nullptr;
    }

    BtNode(char c)
    {
        data = c;
        left = nullptr;
        right = nullptr;
    }
};

BtNode *createBinaryTreeFromFile(const std::string fileName)
{
    std::ifstream input(fileName);
    if (!input)
    {
        std::cerr << "open file " << fileName << " failed\n";
        return nullptr;
    }

    std::vector<BtNode *> nodes;
    char data;
    bool l, r;
    BtNode *root = new BtNode;
    BtNode *node;
    std::string line;

    while (input >> line)
    {
        if (line[0] == '/' && line[1] == '/')
        {
            continue;
        }
        else
        {
            break;
        }
    }

    if (line != "BinaryTree")
    {
        std::cerr << "file format error.\n";
        return nullptr;
    }

    nodes.push_back(root);

    while (input >> data >> l >> r)
    {

        //std::cout << data << l << r << std::endl;
        node = nodes.back();
        nodes.pop_back();

        node->data = data;

        if (r)
        {
            BtNode *tmp = new BtNode();
            node->right = tmp;
            nodes.push_back(tmp);
        }

        if (l)
        {
            BtNode *tmp = new BtNode();
            node->left = tmp;
            nodes.push_back(tmp);
        }
    }

    return root;
}

void advancedOrder(BtNode *root,
                   const std::function<void(BtNode *)> &pre,
                   const std::function<void(BtNode *)> &mid,
                   const std::function<void(BtNode *)> &post)
{
    if (root)
    {
        pre(root);
        advancedOrder(root->left, pre, mid, post);
        mid(root);
        advancedOrder(root->right, pre, mid, post);
        post(root);
    }
}

void doNothing(BtNode *){};
void printNodeData(BtNode *node)
{
    std::cout << node->data << ' ';
}

//========================================================================
// PROBLEM 1
auto preOrder = std::bind(advancedOrder, std::placeholders::_1, printNodeData, doNothing, doNothing);
auto midOrder = std::bind(advancedOrder, std::placeholders::_1, doNothing, printNodeData, doNothing);
auto postOrder = std::bind(advancedOrder, std::placeholders::_1, doNothing, doNothing, printNodeData);

//========================================================================

//========================================================================
// PROBLEM 2

void midOrderHeight(BtNode *root)
{
    int height = 0;
    auto pre = [&height](BtNode *) { ++height; };
    auto post = [&height](BtNode *) { --height; };
    auto printHeight = [&height](BtNode *node) {
        std::cout << "(Data, Height) = ("
                  << node->data << ", " << height << ')'
                  << std::endl;
    };
    advancedOrder(root, pre, printHeight, post);
}

//========================================================================
// PROBELM 3

size_t treeHeight(BtNode *root)
{
    size_t height = 0;
    size_t maxHeight = 0;
    auto pre = [&height](BtNode *) { ++height; };
    auto post = [&height](BtNode *) { --height; };
    auto checkMax = [&height, &maxHeight](BtNode *) {
        if (height > maxHeight)
        {
            maxHeight = height;
        }
    };
    advancedOrder(root, pre, checkMax, post);
    return maxHeight;
}

//========================================================================
// PROBELM 4

size_t treeNodeCount(BtNode *root)
{
    size_t count = 0;
    advancedOrder(root, doNothing, [&count](BtNode *) { ++count; }, doNothing);
    return count;
}

//========================================================================
// PROBELM 5

size_t treeLeafCount(BtNode *root)
{
    size_t count = 0;
    advancedOrder(root, doNothing, [&count](BtNode *root) { root->left || root->right || ++count; }, doNothing);
    return count;
}

//========================================================================
// PROBELM 6

size_t treeNode2DegCount(BtNode *root)
{
    size_t count = 0;
    advancedOrder(root, doNothing, [&count](BtNode *root) { root->left && root->right && ++count; }, doNothing);
    return count;
}

//========================================================================
// PROBELM 7

// return parent
void treeShowNearBy(BtNode* result, const char e);
BtNode *treeFind(BtNode *root, const char e)
{
    BtNode *result = nullptr;
    auto mid = [&result, e](BtNode *root) {
        if (root->left && root->left->data == e)
        {
            result = root;
            return;
        }

        if (root->right && root->left->data == e)
        {
            result = root;
            return;
        }
    };
    advancedOrder(root, doNothing, mid, doNothing);
    treeShowNearBy(result, e);
    return result;
}

void treeShowNearBy(BtNode* result, const char e)
{
    if (result)
    {
        std::cout << "Node : " << e << " found.\n";
        std::cout << "Parent : " << result->data << std::endl;
        BtNode *it, *sibling;

        if (result->left && result->left->data == e)
        {
            it = result->left;
            sibling = result->right;
        }
        else
        {
            it = result->right;
            sibling = result->left;
        }

        if (sibling)
        {
            std::cout << "sibling : " << sibling->data << std::endl;
        }
        else
        {
            std::cout << "no sibling.\n";
        }

        if (it->left)
        {
            std::cout << "left child : " << it->left->data << std::endl;
        }
        else
        {
            std::cout << "no left child\n";
        }

        if (it->right)
        {
            std::cout << "right child : " << it->right->data << std::endl;
        }
        else
        {
            std::cout << "no right child\n";
        }
    }
    else
    {
        std::cout << "Node : " << e << " Not found.\n";
    }
}

//========================================================================
// PROBELM 8

// return height of "e"
size_t treeElemHeight(BtNode* root, char e)
{
    size_t result = 0;
    size_t height = 0;
    auto pre = [&height](BtNode *) { ++height; };
    auto post = [&height](BtNode *) { --height; };
    auto mid = [&height, e, &result](BtNode *root)
    {
        if(root->data == e)
        {
            result = height;
        }
    };
   
    advancedOrder(root, pre, mid, post);
    return result;
}

//========================================================================
// PROBELM 9

std::vector<char> treeLinked2Array(BtNode *root)
{
    std::vector<char> arr;
    arr.resize(512, '#');
    size_t index = 1;
    size_t count = 1;
    auto pre = [&arr, &index](BtNode* root)
    {
        arr[index] = root->data;
        index *=2;
    };

    auto mid = [&arr, &index, &count](BtNode* root)
    {
        ++index;
        ++count;
    };

    auto post = [&arr, &index](BtNode* root)
    {
        index /= 2;
    };

    advancedOrder(root, pre, mid, post);
    arr.resize(count);
    arr[0] = '#';
    return arr;
    
}

BtNode* treeArray2Linked(const std::vector<char>& arr)
{
    size_t index = 1;
    std::vector<BtNode*> nodes;
    nodes.resize(arr.size(), nullptr);
    nodes[0] = new BtNode('#');

    auto p = [](size_t i) { return i/2;};

    BtNode* tmp;
    for(size_t i = 1; i < arr.size(); ++i)
    {
        if(arr[i] != '#')
        {
            tmp = new BtNode(arr[i]);
            nodes[i] = tmp;
            if(i % 2)
            {
                nodes[p(i)]->right = tmp;
            }
            else
            {
                nodes[p(i)]->left = tmp;
            }
        }
    }
    delete nodes[0];
    return nodes[1];
}


//========================================================================
// PROBELM 10

void treeExchangeLR(BtNode* root)
{
    auto pre = [](BtNode * root)
    {
        BtNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    };

    advancedOrder(root, pre, doNothing, doNothing);
}


//========================================================================
// PROBELM 11

BtNode *treeCopy(BtNode* root)
{
    std::vector<BtNode*> nodes;
    std::vector<bool> lrs;
    
    bool flag = true;

    nodes.push_back(new BtNode('#'));

    auto pre = [&nodes, &flag, &lrs](BtNode *root)
    {
        BtNode* tmp = new BtNode(root->data);
        
        if(flag)
        {
            nodes.back()->left = tmp;
        }
        else
        {
            nodes.back()->right = tmp;
        }

        nodes.push_back(tmp);
        lrs.push_back(flag);

        flag = true; // left
    };

    auto mid = [&nodes, &flag, &lrs](BtNode *root)
    {
        flag = false; // right
    };

    auto post = [&nodes, &flag, &lrs](BtNode *root)
    {
        nodes.pop_back();
        flag = lrs.back();
        lrs.pop_back();
    };

    advancedOrder(root, pre, mid, post);

    BtNode* ret = nodes[0]->left;
    delete nodes[0];
    return ret;

}


//========================================================================
// PROBELM 11

void treePath2Leaf(BtNode* root)
{


}

#endif //BINARY_TREE_H