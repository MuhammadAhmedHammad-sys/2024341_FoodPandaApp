#ifndef CWINDOW_H
#define CWINDOW_H

#include <iostream>
#include <string>
using namespace std;

#include "restaurant.h"
#include "customer.h"
#include "menu.h"
#include "Locations.h"

class CustomerWindow
{
private:
    CustomerHashTable *c_hash;
    Restaurants *r_arr;
    CurrentCustomer *user;
    LocationGraph loc_list;

public:
    CustomerWindow(CustomerHashTable *c, Restaurants *r) : c_hash(c), r_arr(r), user(new CurrentCustomer(c)), loc_list() {};

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
        cout<<"4. Open Restaurant\n";
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
            case 4:
                int res_id;
                cout<<"Enter Restaurant ID to open: ";
                cin>>res_id;
                openRestaurant(res_id);
                break;
            default:
                cout<<"Invalid choice!\n";
        }
    };
    
    void displayRestaurants()
    {
        r_arr->chooseSortMethod();
        r_arr->display();
    }

    void openRestaurant(int res_id)
    {
        string res_name = r_arr->getResByID(res_id)->name;
        Menus menu(res_name);
        cout<<"\n========= "<<res_name<<"========\n";
        cout<<"1. View Menu\n";
        cout<<"2. Place Order\n";
        int choice;
        cin>>choice;
        switch(choice)


        {
            case 1:
                cout<<"Displaying menu for "<<res_name<<"\n";
                menu.displayItems();
                break;
            case 2:
                takeOrder(menu, res_id);
                break;
            default:
                cout<<"Invalid choice!\n";
        }
    }

    void takeOrder(Menus &menu, int res_id)
    {
        int total_price = 0;
        string item_id;
        bool ordering = true;
        while(ordering)
        {
            cout<<"Enter item id to add to order (or 'done' to finish): ";
            cin>>item_id;
            if(item_id == "done")
            {
                ordering = false;
            }
            else
            {
                Item_Node* item = menu.search(stoi(item_id));
                if(!item)
                {
                    cout<<"Item not found!\n";
                    continue;
                }
                total_price += item->price;
                cout<<item->name<<" added to order. Current total: "<<total_price<<"\n";
            }
        }
        cout<<"Calculating delivery path...\n\t";
        loc_list.displayPath(loc_list.findPath(r_arr->getResByID(res_id)->loc_id, user->getLocID()));
        user->addOrder(res_id, total_price);
        cout<<"Order placed! Total price: "<<total_price<<"\n";
    }

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