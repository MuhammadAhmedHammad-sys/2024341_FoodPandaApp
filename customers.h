#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Locations.h"

class Customer
{
private:
    string filename;
    string Username;
    bool verified = false;

public:
    Customer(string file = "customer/customer_credentials.txt")
    {
        this->filename = file;
    }

    bool login(string username, string password)
    {
        ifstream fileHandle(filename);
        string temp_username, temp_password;
        while (getline(fileHandle, temp_username) && getline(fileHandle, temp_password))
        {
            if (temp_username == username && temp_password == password)
            {
                this->Username = temp_username;
                this->verified = true;
                fileHandle.close();
                return true;
            }
        }
        fileHandle.close();

        cerr << "Username and Password do not match" << endl;
        return false;
    }

    bool signup(string username, string password, string Location)
    {
        ifstream fileHandle(filename);
        class LocationGraph locGraph;
        int loc_code = locGraph.locationToCode(Location);
        if (loc_code == -1)
        {
            cerr << "Invalid Location. Please choose a valid location." << endl;
            return false;
        }
        string temp_username;
        while (getline(fileHandle, temp_username))
        {
            if (temp_username == username)
            {
                fileHandle.close();
                cerr << "Username already exists. Please choose a different username." << endl;
                return false;
            }
            getline(fileHandle, temp_username); // skip password line
        }
        fileHandle.close();

        ofstream outFile(filename, ios::app);
        ofstream userFile("customer/" + username + ".txt");
        if (outFile.is_open() && userFile.is_open())
        {
            outFile << username << endl;
            outFile << password << endl;
            outFile.close();
            cout << "Signup successful! You can now log in." << endl;

            userFile << "Location: " << loc_code << endl;
            userFile.close();

            this->Username = username;
            this->verified = true;

            return true;
        }
        if (!outFile.is_open())
            cerr << "Error: Unable to open file for writing." << endl;
        if (!userFile.is_open())
            cerr << "Error: Unable to create user file." << endl;
        return false;
    }

    void customerWindow()
    {
        cout << "========= Customer Panel =========" << endl;
        if (!verified)
        {
            cout << "Login (1) / Signup (2): ";
            int choice;
            cin >> choice;
            string username, password;
            switch (choice)
            {
            case 1:
            {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                if (!login(username, password))
                {
                    cout << "Login failed. Please try again." << endl;
                    return;
                }
                break;
            }
            case 2:
            {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                string location;
                cout << "Enter Location: ";
                cin >> location;
                if (!signup(username, password, location))
                {
                    return;
                }
                break;
            }
            default:
                break;
            }
        }

        while (verified)
        {
            cout << "Welcome, " << this->Username << " !" << endl
                 << "Loading Data..." << endl
                 << endl;
            int choice;
            cout << "Menu:" << endl;
            // Add customer functionalities here
        }
    }
};

#endif