#include <iostream>
#include <fstream>
using namespace std;

struct Item_Node
{ // Structure representing a single food item in a menu
    Item_Node *lchild;
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

    Item_Node *RInsert(Item_Node *p, int price, string name)
    {
        Item_Node *t;

        if (p == nullptr)
        {
            t = new Item_Node;
            t->price = price;
            t->name = name;
            t->lchild = nullptr;
            t->rchild = nullptr;
            t->height = 1;
            return t;
        }

        if (price > p->price)
        {
            p->rchild = RInsert(p->rchild, price, name);
        }

        else if (price < p->price)
        {
            p->lchild = RInsert(p->lchild, price, name);
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

    void insertItem(int price, string name)
    {
        root = RInsert(root, price, name);
        changes = true;
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