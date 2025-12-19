#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
using namespace std;

class Restaurant
{
private:
    string filename;
    string adminUsername;
    string adminPassword;
    bool verified=false;

public:
    Restaurant()
    {

    }

    bool verifyCredentials(string username, string password)
    {
        if (username == adminUsername && password == adminPassword)
        {
            verified = true;
            return true;
        }
        return false;
    }

    void restaurantWindow()
    {
        cout << "========= Restaurant Panel =========" << endl;
        if (!verified)
        {
            string username, password;
            cout << "Enter Manager Username: ";
            cin >> username;
            cout << "Enter Manager Password: ";
            cin >> password;

            if (!verifyCredentials(username, password))
            {
                cout << "Invalid credentials. Access denied." << endl;
                return;
            }
        }

        while (true)
        {
            cout << "Welcome, Chef!" << endl
                 << "Loading Data..." << endl
                 << endl;

            int choice;
            cout << "Menu:" << endl;
            cout << "\t1. View Menu" << endl;
            cout << "\t2. Add Item" << endl;
            cout << "\t3. Remove Item" << endl;
            cout << "\t4. Save and Exit Restaurant Panel" << endl;
            cout << "\t5. Change Restaurant Credentials" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:

                break;
            case 2:
            {

                break;
            }
            case 3:
            {

                break;
            }
            case 4:
 
                cout << "Data saved. Exiting Restaurant Panel." << endl;
                return;
            case 5:
            {

                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

#endif