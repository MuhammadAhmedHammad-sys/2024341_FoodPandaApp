#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
using namespace std;

struct Item_Node
{ // Structure representing a single food item in a menu
    Item_Node *lchild;
    int sr_no;
    int price;
    string name;
    Item_Node *rchild;
    int height;
};

class Menus // AVL tree stores menu for a restaurant
{
private:
    Item_Node *root;
    bool changes;
    string res_name; // Restaurant name

public:
    Menus(string res_name)
    {
        root = nullptr;
        changes = false;
        this->res_name = res_name;
        loadMenu();
    }

    int NodeHeight(Item_Node *p)
    {
        int hl, hr;

        if (p && p->lchild)
        {
            hl = p->lchild->height;
        }

        else
        {
            hl = 0;
        }

        if (p && p->rchild)
        {
            hr = p->rchild->height;
        }

        else
        {
            hr = 0;
        }

        if (hl > hr)
        {
            return hl + 1;
        }

        else
        {
            return hr + 1;
        }
    }

    int BF(Item_Node *p)
    {
        int hl, hr;

        if (p && p->lchild)
        {
            hl = p->lchild->height;
        }

        else
        {
            hl = 0;
        }

        if (p && p->rchild)
        {
            hr = p->rchild->height;
        }

        else
        {
            hr = 0;
        }

        return hl - hr;
    }

    Item_Node *LLRotation(Item_Node *p)
    {
        Item_Node *pl = p->lchild;
        Item_Node *plr = pl->rchild;

        pl->rchild = p;
        p->lchild = plr;

        p->height = NodeHeight(p);
        pl->height = NodeHeight(pl);

        if (p == root)
        {
            root = pl;
        }

        return pl;
    }

    Item_Node *LRRotation(Item_Node *p)
    {
        Item_Node *pl = p->lchild;
        Item_Node *plr = pl->rchild;

        pl->rchild = plr->lchild;
        p->lchild = plr->rchild;

        plr->rchild = p;
        plr->lchild = pl;

        p->height = NodeHeight(p);
        pl->height = NodeHeight(pl);
        plr->height = NodeHeight(plr);

        if (p == root)
        {
            root = plr;
        }

        return plr;
    }

    Item_Node *RLRotation(Item_Node *p)
    {
        Item_Node *pr = p->rchild;
        Item_Node *prl = pr->lchild;

        p->rchild = prl->lchild;
        pr->lchild = prl->rchild;

        prl->lchild = p;
        prl->rchild = pr;

        pr->height = NodeHeight(pr);
        p->height = NodeHeight(p);
        prl->height = NodeHeight(prl);

        if (root == p)
        {
            root = prl;
        }

        return prl;
    }

    Item_Node *RRRotation(Item_Node *p)
    {
        Item_Node *pr = p->rchild;
        Item_Node *prl = pr->lchild;

        pr->lchild = p;
        p->rchild = prl;

        p->height = NodeHeight(p);
        pr->height = NodeHeight(pr);

        if (p == root)
        {
            root = pr;
        }

        return pr;
    }

    Item_Node *RInsert(Item_Node *p, Item_Node i)
    {
        Item_Node *t;

        if (p == nullptr)
        {
            t = new Item_Node;
            t->price = i.price;
            t->name = i.name;
            t->sr_no = i.sr_no;
            t->lchild = nullptr;
            t->rchild = nullptr;
            t->height = 1;
            return t;
        }

        if (i.sr_no > p->sr_no)
        {
            p->rchild = RInsert(p->rchild, i);
        }

        else if (i.sr_no < p->sr_no)
        {
            p->lchild = RInsert(p->lchild, i);
        }

        p->height = NodeHeight(p);

        if (BF(p) == 2 && BF(p->lchild) == 1)
        {
            return LLRotation(p);
        }

        else if (BF(p) == 2 && BF(p->lchild) == -1)
        {
            return LRRotation(p);
        }

        else if (BF(p) == -2 && BF(p->rchild) == 1)
        {
            return RLRotation(p);
        }

        else if (BF(p) == -2 && BF(p->rchild) == -1)
        {
            return RRRotation(p);
        }

        return p;
    }

    void insertItem(Item_Node i)
    {
        root = RInsert(root, i);
        changes = true;
    }

    Item_Node *search(int key)
    {
        Item_Node *p = root;

        while (p != nullptr)
        {
            if (key == p->sr_no)
            {
                return p;
            }

            else if (key > p->sr_no)
            {
                p = p->rchild;
            }

            else
            {
                p = p->lchild;
            }
        }

        return nullptr;
    }

    void loadMenu()
    {
        string filename = "menus" + res_name + "_menu.txt";
        ifstream file(filename);
        Item_Node temp;
        string sr_no, price;
        while (getline(file, sr_no) && getline(file, price) && getline(file, temp.name))
        {
            temp.sr_no = stoi(sr_no);
            temp.price = stoi(price);
            insertItem(temp);
        }
    }

    void writeToFile(Item_Node *p, ofstream &file)
    {
        if (p)
        {
            writeToFile(p->lchild, file);
            file << p->name << endl;
            file << p->price << endl;
            writeToFile(p->rchild, file);
        }
    }

    bool saveToFile()
    {
        string filename = "menus/" + res_name + "_menu.txt";
        ofstream file(filename, ios::trunc);
        if (!file.is_open())
        {
            return false;
        }

        Item_Node *p = root;

        writeToFile(p, file);
        file << endl;

        file.close();
        changes = false;
        return true;
    }

    ~Menus()
    {
        if (changes)
        {
            saveToFile();
        }
    }
};

#endif