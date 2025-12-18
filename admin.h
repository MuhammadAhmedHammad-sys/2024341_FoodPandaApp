#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Locations.h"

class Admin
{
private:
    string filename;
    string adminUsername;
    string adminPassword;
    bool verified = false;

public:
    Admin(string file = "admin/admin_credentials.txt")
    {
        this->filename = file;
        loadCredentials();
    }

    void loadCredentials()
    {
        ifstream fileHandle(filename);
        if (fileHandle.is_open())
        {
            getline(fileHandle, adminUsername);
            getline(fileHandle, adminPassword);
            fileHandle.close();
        }
        else
        {
            cerr << "Error: Unable to open admin credentials file." << endl;
        }
    }

    void saveCredentials()
    {
        ofstream fileHandle(filename);
        if (fileHandle.is_open())
        {
            fileHandle << adminUsername << endl;
            fileHandle << adminPassword << endl;
            fileHandle.close();
        }
        else
        {
            cerr << "Error: Unable to open admin credentials file for writing." << endl;
        }
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

    void changeCredentials(string newUsername, string newPassword)
    {
        adminUsername = newUsername;
        adminPassword = newPassword;
        saveCredentials();
    }

    void adminWindow()
    {
        cout << "========= Admin Panel =========" << endl;
        if (!verified)
        {
            string username, password;
            cout << "Enter Admin Username: ";
            cin >> username;
            cout << "Enter Admin Password: ";
            cin >> password;

            if (!verifyCredentials(username, password))
            {
                cout << "Invalid credentials. Access denied." << endl;
                return;
            }
        }

        while (true)
        {
            cout << "Welcome, Admin!" << endl
                 << "Loading Data..." << endl
                 << endl;
            LocationGraph locGraph;
            int choice;
            cout << "Menu:" << endl;
            cout << "\t1. View Locations" << endl;
            cout << "\t2. Add Location" << endl;
            cout << "\t3. Add Connection between Locations" << endl;
            cout << "\t4. Save and Exit Admin Panel" << endl;
            cout << "\t5. Change Admin Credentials" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                locGraph.printGraph();
                break;
            case 2:
            {
                int code;
                string name;
                cout << "Enter Location Code (integer): ";
                cin >> code;
                cout << "Enter Location Name: ";
                cin.ignore(); // To ignore the newline character left by previous input
                getline(cin, name);
                if (locGraph.addLocation(code, name))
                {
                    cout << "Location added successfully." << endl;
                }
                else
                {
                    cout << "Location code already exists." << endl;
                }
                break;
            }
            case 3:
            {
                int from, to;
                cout << "Enter 'from' Location Code: ";
                cin >> from;
                cout << "Enter 'to' Location Code: ";
                cin >> to;
                locGraph.addEdge(from, to);
                cout << "Connection added successfully." << endl;
                break;
            }
            case 4:
                locGraph.saveToFile();
                cout << "Data saved. Exiting Admin Panel." << endl;
                return;
            case 5:
            {
                string newUsername, newPassword;
                cout << "Enter new Admin Username: ";
                cin >> newUsername;
                cout << "Enter new Admin Password: ";
                cin >> newPassword;
                changeCredentials(newUsername, newPassword);
                loadCredentials(); // Reload to ensure consistency
                cout << "Admin credentials updated successfully." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

#endif