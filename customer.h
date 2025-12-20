#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Customer
{
    string username;
    string password;
    int location_code;
};

struct CustomerNode
{
    Customer data;
    CustomerNode *next;
    CustomerNode(Customer d, CustomerNode *n) : data(d), next(n) {};
};

class CustomerHashTable
{
private:
    CustomerNode **table;
    int size = 0;
    int items = 0;
    bool changes = false;

public:
    CustomerHashTable()
    {
        const string fileName = "customer/customers.txt";

        ifstream file(fileName);
        string line;
        while (getline(file, line) && getline(file, line) && getline(file, line))
            this->size++;
        file.close();

        this->size = 3 * size + 13;
        this->table = new CustomerNode *[size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;

        loadCustomers();
    }

    int hash(const string &user_name)
    {
        unsigned int hash = 5381;
        for (char c : user_name)
        {
            hash = hash * 31 + c;
        }
        return hash % this->size;
    }

    void insert(const Customer &user)
    {
        int hash_code = hash(user.username);
        CustomerNode *head = table[hash_code];
        table[hash_code] = new CustomerNode{user, head};
        items++;
    }

    void loadCustomers(const string &fileName = "customer/customers.txt")
    {
        ifstream file(fileName);
        Customer temp;
        string loc_code;
        while (getline(file, temp.username) && getline(file, temp.password) && getline(file, loc_code))
        {
            temp.location_code = stoi(loc_code);
            insert(temp);
        }
    }

    void insertNew(const Customer &user)
    {
        insert(user);
        this->changes = true;
    }

    Customer *find(const string &username)
    {
        int hash_code = hash(username);
        CustomerNode *node = table[hash_code];
        while (node)
        {
            if (node->data.username == username)
                return &(node->data);
            node = node->next;
        }
        return nullptr;
    }

    bool remove(const string &username)
    {
        int hash_code = hash(username);
        CustomerNode *node = table[hash_code];
        CustomerNode *prev = nullptr;

        while (node)
        {
            if (node->data.username == username)
            {
                if (prev)
                    prev->next = node->next;
                else
                    table[hash_code] = node->next;
                delete node;
                items--;
                changes = true;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    bool saveToFile(const string &fileName = "customer/customers.txt")
    {
        ofstream file(fileName, ios::trunc);
        if (!file.is_open())
            return false;

        for (int i = 0; i < size; i++)
        {
            CustomerNode *node = table[i];
            while (node)
            {
                file << node->data.username << "\n";
                file << node->data.password << "\n";
                file << node->data.location_code << "\n";
                node = node->next;
            }
        }

        file.close();
        changes = false;
        return true;
    }

    ~CustomerHashTable()
    {
        if (changes)
            saveToFile();

        for (int i = 0; i < size; i++)
        {
            CustomerNode *node = table[i];
            while (node)
            {
                CustomerNode *tmp = node;
                node = node->next;
                delete tmp;
            }
        }
        delete[] table;
    }

    friend class CurrentCustomer;
};

struct OrderRecord
{
    int restrauntID;
    int price;
};

struct OrderNode
{
    OrderRecord order;
    OrderNode *next;
    OrderNode(OrderRecord o, OrderNode *n) : order(o), next(n) {};
};

class CurrentCustomer
{
private:
    CustomerHashTable *HashTable;
    Customer user;
    OrderNode *head; // store order history
    bool verified = false;
    bool changes = false;

public:
    CurrentCustomer(CustomerHashTable *table) : HashTable(table), head(nullptr), verified(false) {};

    bool verify(const string &user_name, const string &password)
    {
        if (!HashTable)
            return false;

        Customer *found = HashTable->find(user_name);
        if (!found)
            return false;

        if (found->password == password)
        {
            user = *found; // copy customer data
            verified = true;
            return true;
        }

        return false;
    }

    bool login(const string &user_name, const string &password)
    {
        if (verify(user_name, password))
        {
            loadOrderHistory(user_name);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool signup(const string &user_name, const string &password, int &loc_code)
    {
        if (!HashTable)
            return false;

        Customer *found = HashTable->find(user_name);
        if (found)
            return false;

        HashTable->insertNew({user_name, password, loc_code});
        return login(user_name, password);
    };

    string fileName(const string &username)
    {
        return "customer/" + username + "_details.txt";
    }

    void clearOrders()
    {
        while (head)
        {
            OrderNode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    bool loadOrderHistory(const string &username)
    {
        clearOrders();

        ifstream file(fileName(username));

        if (file.is_open())
        {
            OrderRecord temp;
            while (file >> temp.restrauntID && file >> temp.price)
            {
                head = new OrderNode(temp, head);
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    void addOrder(int restrauntID, int price)
    {
        OrderRecord newOrder = {restrauntID, price};
        head = new OrderNode(newOrder, head);
        changes = true;
    }

    OrderNode* getOrderHistory()
    {
        return head;
    }

    int getLocID()
    {
        return user.location_code;
    }

    bool saveToFile()
    {
        ofstream file(fileName(user.username), ios::trunc);
        if (!file.is_open())
            return false;

        for (OrderNode *current = head; current; current = current->next)
        {
            file << current->order.restrauntID << '\n';
            file << current->order.price << '\n';
        }

        file.close();
        changes = false;
        return true;
    }

    ~CurrentCustomer()
    {
        if (changes)
            saveToFile();

        clearOrders();
    }
};

#endif
