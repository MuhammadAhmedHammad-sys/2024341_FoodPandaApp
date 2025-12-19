#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Restaurant
{
private:
    string filename;
    string managerUsername;
    string managerPassword;
    bool verified=false;

public:
    Restaurant(string file = "restaurant/restaurant_credentials.txt")
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
                this->managerUsername = temp_username;
                this->managerPassword = temp_password;
                this->verified=true;
                fileHandle.close();
                return true;
            }
        }
        fileHandle.close();

        cerr << "Username and Password do not match" << endl;
        return false;
    }

    bool signup(string username, string password){
        ifstream fileHandle(filename);
        string temp_username, temp_password;
        while (getline(fileHandle, temp_username))
        {
            if (temp_username == username)
            {
                fileHandle.close();
                cerr <<"Username already exists. Please choose a different username." << endl;
                return false;    
            }
        }
        fileHandle.close();

        ofstream outFile(filename, ios::app);
        if (outFile.is_open())
        {
            outFile << username << endl;
            outFile << password << endl;
            outFile.close();
            cout << "Signup successful! You can now log in." << endl;

            this->managerUsername = username;
            this->managerPassword = password;
            this->verified = true;

            return true;
        }
        if (!outFile.is_open())
            cerr << "Error: Unable to open file for writing." << endl;
        return false;    
    }

    void restaurantWindow()
    {
        cout << "========= Restaurant Panel =========" << endl;
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
                for (int attempts = 0; true; attempts++)
                {
                    cout << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    cin >> password;
                    if (login(username, password))
                    {
                        cout << "Log-in Successfull!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Login Failed..." << endl
                             << (attempts < 3 ? ("Please Try Again (" + to_string(3 - attempts) + " attempts left)") : "Maximum Attempts Reached. Aborting...") << endl;
                    }
                    if (attempts == 3)
                    {
                        return;
                    }
                }
            break;
            }
            case 2:
            {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                if (!signup(username, password))
                {
                    cout << "Sign-up Unsuccessful... Try Again (N/n to Abort)?";
                    string choice;
                    cin >> choice;
                    if (choice == "N" || choice =="n")
                    {   
                        return;
                    }
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

        // while (verified)
        // {
        //     cout << "Welcome, " << this->managerUsername << "!" << endl
        //          << "Loading Data..." << endl
        //          << endl;

        // }
        
    }
};

#endif