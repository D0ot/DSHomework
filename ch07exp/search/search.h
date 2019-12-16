#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <iostream>

struct Node
{
    Node(Node *l, Node *r, int d) : left(l), right(r), data(d){};
    Node *left;
    Node *right;
    int data;
};

int binarySearch(const std::vector<int> &arr, const int l, const int r, const int x)
{
    int mid = (r - l) / 2 + l; // prevent overflow
    std::cout << "Step         : " << l << '\t' << r << '\t' << mid << std::endl;
    if (l > r)
    {
        return -1;
    }

    if (arr[mid] > x)
    {
        return binarySearch(arr, l, mid - 1, x);
    }
    else if (arr[mid] < x)
    {
        return binarySearch(arr, mid + 1, r, x);
    }
    else
    {
        return mid;
    }
}

int binarySearch(const std::vector<int> &arr, const int x)
{
    std::cout << "BinarySearch : "
              << "Low\tHigh\tMid\n";
    binarySearch(arr, 0, arr.size() - 1, x);
}

void insertOrder(Node *&root, int x)
{
    if (root)
    {
        if (x < root->data)
        {
            insertOrder(root->left, x);
        }
        else
        {
            insertOrder(root->right, x);
        }
    }
    else
    {
        root = new Node(nullptr, nullptr, x);
    }
}

void preOrder(Node *root)
{
    if (!root)
    {
        return;
    }

    std::cout << root->data << ' ';
    preOrder(root->left);
    preOrder(root->right);
}

void midOrder(Node *root)
{
    if(!root)
    {
        return;
    }

    midOrder(root->left);
    std::cout << root->data << ' ';
    midOrder(root->right);

}


void showTree(Node* root)
{
    std::cout << "Pre Order :";
    preOrder(root);
    std::cout << "\nMid Order :";
    midOrder(root);
    std::cout << "\n";
}

Node *createByVector(const std::vector<int> &ds)
{

    Node *t1 = nullptr;

    for (auto &&x : ds)
    {
        insertOrder(t1, x);
    }
    return t1;
}


// input is sequential
Node* createBlanceByVector(const std::vector<int> &ds, int l, int r)
{
    if(l > r)
    {
        return nullptr;
    }


    if(l == r)
    {
        return (new Node(nullptr, nullptr, ds[l]));
    }

    int mid = (r - l) / 2 + l;

    return new Node(createBlanceByVector(ds, l, mid-1), createBlanceByVector(ds, mid+1, r), ds[mid]);
}


Node* searchInTree(Node* root, const int x)
{
    if(root)
    {
        if(x < root->data)
        {
            return searchInTree(root->left, x);
        }else if(x > root->data)
        {
            return searchInTree(root->right, x);
        }else
        {
            return root;
        }
    }else
    {
        return nullptr;
    }
}

Node* findMax(Node* root)
{
    if(!root)
    {
        return nullptr;
    }

    Node* iter = root;
    while(iter->right)
    {
        iter = iter->right;
    }
    return iter;
}

Node* findMin(Node* root)
{
    if(!root)
    {
        return nullptr;
    }

    Node* iter = root;
    while(iter->left)
    {
        iter = iter->left;
    }
    return iter;
}



bool deleteInTree(Node* root, const int x)
{
    Node* iter = root;

    while(iter)
    {
        if(x < iter->data)
        {
            if(iter->left)
            {
                if(iter->left->data == x)
                {
                    if(iter->left->left == nullptr)
                    {
                        Node *tmp = iter->left->right;
                        delete iter->left;
                        iter->left = tmp;
                        return true;
                    }

                    if(iter->left->right == nullptr)
                    {
                        Node* tmp = iter->left->left;
                        delete iter->left;
                        iter->left = tmp;
                        return true;
                    }
                    Node *rcMin = findMin(iter->left);
                    int data = rcMin->data;
                    deleteInTree(iter->left, rcMin->data);
                    iter->left->data = data;
                    return true;
                }
                else
                {
                    iter=iter->left;
                }
            }else
            {
                return false;
            }
        }
        else
        {
            if(iter->right)
            {
                if(iter->right->data == x)
                {
                    if(iter->right->left == nullptr)
                    {
                        Node*tmp = iter->right->right;
                        delete iter->right;
                        iter->right = tmp;
                        return true;
                    }

                    if(iter->right->right == nullptr)
                    {
                        Node*tmp = iter->right->left;
                        delete iter->right;
                        iter->right = tmp;
                        return true;
                    }

                    Node *lcMax = findMax(iter->right);
                    int data = lcMax->data;
                    deleteInTree(iter->right, data);
                    iter->right->data = data;
                    return true;

                }else
                {
                    iter=iter->right;
                }

            }else
            {
                return false;
            }
        }
    }

    return false;

}

#endif