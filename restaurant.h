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
        loadRestaurants();
    }

    void add_res(Res_Node r)
    {
        if (res_count >= MAX)
        {
            cout << "Restaurant list full\n";
            return;
        }

        res_arr[res_count] = r;
        res_count += 1;
        changes = true;
    }

    void chooseSortMethod()
    {
        int option;
        do
        {
            cout << "Sort Restaurants: " << endl;
            cout << "1. Sort by ID: " << endl;
            cout << "2. Sort by Rating: " << endl;
            cout << "Select an option: ";
            cin >> option;
            switch (option)
            {
            case 1:
            {
                sortByID(res_arr, res_count);
                break;
            }

            case 2:
            {
                sortByRating(res_arr, res_count);
                break;
            }

            default:
                cout << "Invalid choice!\n";
                break;
            }
        } while (option != 3);
    }

    void sortByID(Res_Node A[], int n)
    {
        int x;

        for (int i = 1; i < n; i++)
        {
            int j = i - 1;
            x = A[i].id;

            while (j > -1 && A[j].id > x)
            {
                A[j + 1].id = A[j].id;
                j--;
            }

            A[j + 1].id = x;
        }
    }

    void sortByRating(Res_Node A[], int n)
    {
        int x;

        for (int i = 1; i < n; i++)
        {
            int j = i - 1;
            x = A[i].rating;

            while (j > -1 && A[j].rating > x)
            {
                A[j + 1].rating = A[j].rating;
                j--;
            }

            A[j + 1].rating = x;
        }
    }

    Res_Node* getResByID(int res_id)
    {
        for (int i = 0; i < res_count; i++)
        {
            if (res_arr[i].id == res_id)
            {
                return &res_arr[i];
            }
        }
        return nullptr; // not found
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

    void loadRestaurants(const string &filename = "restaurants/restaurants.txt")
    {
        ifstream file(filename);
        Res_Node temp;
        string id, rating, loc_id;
        while (getline(file, id) && getline(file, temp.name) && getline(file, rating) && getline(file, loc_id))
        {
            temp.id = stoi(id);
            temp.rating = stoi(rating);
            temp.loc_id = stoi(loc_id);
            add_res(temp);
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