#ifndef TREE_H
#define TREE_H

#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../binarytree/binarytree.h"

typedef BtNode Tree;

Tree *CreateTreeFromFile(const std::string fn)
{
    std::ifstream input(fn);

    std::map<char, Tree *> nodes;
    nodes['#'] = new BtNode('#');
    std::string line;

    char first;
    bool fSignFound = false;
    bool fFullLineFound = false;
    while (getline(input, line))
    {
        //std::cout << "Line START:\n" << line << std::endl;
        //std::cout << "Line END\n";
        if (line.size() <= 1)
        {
            continue;
        }

        if (line[0] == '/' && line[1] == '/')
        {
            //   std::cout << "commended line" << std::endl;
            continue;
        }

        auto i = line.cbegin();
        while (i != line.cend())
        {
            if (*i != ' ')
            {
                break;
            }
            ++i;
        }

        if (i == line.cend())
        {
            continue;
        }

        if (!fSignFound)
        {
            while (i != line.cend() && *i != 'T')
            {
                ++i;
            }

            if (*i == 'T')
            {
                //std::cout << line <<std::endl;
                fSignFound = true;
            }
            continue;
        }

        if (!fFullLineFound)
        {
            first = *i;
            //std::cout << "first is " << *i << std::endl;
            fFullLineFound = true;
            continue;
        }

        char parent = line[0];
        char child = line[2];

        auto addPair = [](BtNode *p, BtNode *c) {
            if (p->left)
            {
                BtNode *tmp = p->left;
                while (tmp->right)
                {
                    tmp = tmp->right;
                }
                tmp->right = c;
            }
            else
            {
                p->left = c;
            }
        };

        BtNode *pnode = nodes[parent];

        if (!pnode)
        {
            pnode = new BtNode(parent);
            nodes[parent] = pnode;
            addPair(nodes['#'], pnode);
        }

        BtNode *cnode = new BtNode(child);
        nodes[child] = cnode;

        //std::cout << "Before Add op\n";

        addPair(pnode, cnode);
    }

    return nodes['#'];
}

void forestPreOrder(Tree *t)
{
    preOrder(t);
}

void forestPostOrder(Tree *t)
{
    // son forest and next sibling
    midOrder(t);
}

void forestLevelOrder(Tree *t)
{
    std::queue<Tree *> qu;
    qu.push(t);

    Tree *tmp;
    while (!qu.empty())
    {
        tmp = qu.front();
        qu.pop();
        while (tmp)
        {
            std::cout << tmp->data << ' ';
            if (tmp->left)
            {
                qu.push(tmp->left);
            }
            tmp = tmp->right;
        }
    }
}

int forestHeight_inner(Tree *t)
{
    if (t == NULL)
    {
        return 0;
    }

    int son = forestHeight_inner(t->left) + 1;

    int sib = forestHeight_inner(t->right);

    if (son > sib)
    {
        return son;
    }
    return sib;
}

int forestHeight(Tree *t)
{
    return forestHeight_inner(t) - 1;
}

int forestNodeCount(Tree *t)
{
    return treeNodeCount(t) - 1;
}

int forestLeafCount(Tree *t)
{
    if (t == NULL)
    {
        return 0;
    }

    if (t->left == NULL)
    {
        return 1 + forestLeafCount(t->right);
    }

    return forestLeafCount(t->left) + forestLeafCount(t->right);
}

int forestDegree(Tree *t)
{
    if (t == NULL)
    {
        return 0;
    }

    int max = 1;

    int sibMax = 0;

    Tree *tmp = t;
    while (tmp)
    {
        ++max;
        int thisTimeMax = forestDegree(tmp->left);

        if (thisTimeMax > sibMax)
        {
            sibMax = thisTimeMax;
        }

        tmp = tmp->left;
    }

    if (max > sibMax)
    {
        return max;
    }
    else
    {
        return sibMax;
    }
}

void forestLNPreOrder(Tree *t, int level)
{
    if (t == NULL)
    {
        return;
    }

    std::cout << '(' << t->data << ' ' << ',' << level << ')' << ' ';

    forestLNPreOrder(t->left, level + 1);
    forestLNPreOrder(t->right, level);
}

void forestLNPreOrder(Tree *t)
{
    forestLNPreOrder(t, 0);
}

std::string forestGerenalOutput(Tree *t)
{
    if (t == NULL)
    {
        return "";
    }

    std::string ret;

    std::string tmp;

    if (t->left)
    {

        tmp = t->data + ("(" + forestGerenalOutput(t->left) + ")");
    }
    else
    {
        tmp = t->data;
    }

    ret = tmp;
    tmp = forestGerenalOutput(t->right);

    if (tmp.size() != 0)
    {
        ret += ',' + tmp;
    }

    return ret;
}

#endif // TREE_H