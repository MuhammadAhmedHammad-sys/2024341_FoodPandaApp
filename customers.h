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
    LocationGraph locGraph;

public:
    Customer(string file = "customer/customer_credentials.txt") : filename(file), locGraph() {
                                                                  };

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

    int getLocation()
    {
        ifstream userFile("customer/" + this->Username + ".txt");
        string line;
        if (userFile.is_open())
        {
            while (getline(userFile, line))
            {
                if (line.find("Location: ") == 0)
                {
                    string loc_code_str = line.substr(10);
                    return stoi(loc_code_str);
                }
            }
            userFile.close();
        }
        return -1; // Not found
    }

    void updateLocation(int loc)
    {
        cout << "Not implemented yet" << endl;
    };

    void customerWindow()
    {
        cout << "========= Customer Panel =========" << endl;
        if (!verified)
        {
            cin.clear();
            cout << "Login (1) / Signup (2): ";
            int choice;
            cin >> choice;
            string username, password;
            switch (choice)
            {
            case 1:
            {
                for (int attempts = 0; true; attempts++)
                {
                    cout << endl
                         << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    cin >> password;
                    if (login(username, password))
                    {
                        cout << "Login Successfull!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Login Failed... " << endl
                             << (attempts < 3 ? ("Please Try Again (" + to_string(3 - attempts) + " attempts left)") : "Maximum Attempts Reached. Aborting...") << endl;
                    }
                    if (attempts == 3)
                        return;
                }
                break;
            }
            case 2:
            {
                while (!verified)
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
                        cout << "Sign up Unseccefull... Try Again (N/n to Abort)?";
                        string choice;
                        cin >> choice;
                        if (choice == "N" || choice == "n")
                            return;
                    }
                }
                break;
            }
            default:
                break;
            }
        }

        if (!verified)
            return;

        cout << "\nWelcome, " << this->Username << " !" << endl
             << "Loading Data..." << endl
             << endl;

        while (true)
        {

            int choice;
            cout << "Menu:" << endl;
            cout << "\t1. Exit" << endl;
            cout << "\t2. View Location" << endl;
            cout << "\t3. Update Location" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                return;
            case 2:
            {
                int loc_code = getLocation();
                string loc_name = locGraph.codeToLocation(loc_code);
                cout << "Your current location is: " << loc_name << " (Code: " << loc_code << ")" << endl;
                break;
            }
            case 3:
            {
                cout << "Enter new Location: ";
                string new_location;
                cin >> new_location;
                updateLocation(locGraph.locationToCode(new_location));
                break;
            }
            }
            // Add customer functionalities here
        }
    }
};

#endif