#ifndef CWINDOW_H
#define CWINDOW_H

#include <iostream>
#include <string>
using namespace std;

#include "restaurant.h";
#include "customer.h";
#include "menu.h";

class CustomerWindow
{
private:
    CustomerHashTable *c_hash;
    Restaurants *r_arr;
    CurrentCustomer *user;

public:
    CustomerWindow(CustomerHashTable *c, Restaurants *r) : c_hash(c), r_arr(r), user(new CurrentCustomer(c)) {};

    void menu() 
    {
        cout<<"\n===== Customer Menu =====\n";
        cout<<"1. Login\n";
        cout<<"2. Signup\n";
        int choice;
        cin>>choice;
        string username, password;
        switch(choice)
        {
            case 1:
                cout<<"Enter username: ";
                cin>>username;
                cout<<"Enter password: ";
                cin>>password;
                if(user->login(username, password))
                {
                    cout<<"Login successful!\n";
                }
                else
                {
                    cout<<"Login failed! Incorrect username or password.\n";
                }
                break;
            case 2:
                cout<<"Enter desired username: ";
                cin>>username;
                cout<<"Enter desired password: ";
                cin>>password;
                int loc_code;
                cout<<"Enter your location code: ";
                cin>>loc_code;
                if(user->signup(username, password, loc_code))
                {
                    cout<<"Signup successful! You are now logged in.\n";
                }
                else
                {
                    cout<<"Signup failed! Username may already exist.\n";
                }
                break;
            default:
                cout<<"Invalid choice!\n";
        }

        cout<<"\n===== Options =====\n";
        cout<<"1. View Available Restaurants\n";
        cout<<"2. View Order History\n";
        cout<<"3. Logout\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                r_arr->display();
                break;
            case 2:
                displayOrderHistory();
                break;
            case 3:
                cout<<"Logging out...\n";
                break;
            default:
                cout<<"Invalid choice!\n";
        }
    };

    void displayOrderHistory()
    {
        OrderNode* head = user->getOrderHistory();
        if (!head)
        {
            cout << "No order history available.\n";
            return;
        }

        cout << "===== Order History =====\n";
        for (OrderNode* current = head; current; current = current->next)
        {
            cout << "Restaurant ID: " << current->order.restrauntID << ", Price: " << current->order.price << "\n";
        }
    }

    ~CustomerWindow()
    {
        delete user;
    }
};

#endif