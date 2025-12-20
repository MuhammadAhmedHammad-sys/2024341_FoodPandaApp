#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <fstream>
using namespace std;

struct Res_Node
{
    int id;
    string name;
    float rating;
    int loc_id;
};

const int MAX = 100;

class Restaurants
{
private:
    int res_count;
    Res_Node res_arr[MAX]; // res_arr stores all restaurants in an array
    bool changes;

public:
    Restaurants()
    {
        res_count = 0;
        changes = false;
    }

    void add_res(int id, string name, float rating)
    {
        if (res_count >= MAX)
        {
            cout << "Restaurant list full\n";
            return;
        }

        Res_Node r;
        r.id = id;
        r.name = name;
        r.rating = rating;
        res_arr[res_count] = r;
        res_count += 1;
        changes = true;
    }

    void display()
    {
        cout << "===== ALL AVAILABLE RESTAURANTS =====" << endl;
        for (int i = 0; i < res_count; i++)
        {
            cout << res_arr[i].id << " ";
            cout << res_arr[i].name << " ";
            cout << res_arr[i].rating << " ";
            cout << endl;
        }
    }

    bool saveToFile(const string &filename = "restaurants/restaurants.txt")
    {
        ofstream file(filename, ios::trunc);
        if (!file.is_open())
        {
            return false;
        }

        for (int i = 0; i < res_count; i++)
        {
            file << res_arr[i].id << "\n";
            file << res_arr[i].name << "\n";
            file << res_arr[i].rating << "\n";
        }

        file.close();
        changes = false;
        return true;
    }

    ~Restaurants()
    {
        if (changes)
        {
            saveToFile();
        }
    }
};

#endif