#include <iostream>
using namespace
std;

#include "customer.h";
#include "Locations.h";
#include "restaurant.h";

#include "customer_window.h";
#include "restaurant_window.h";

int main()
{

    cout<<"\n================================ FoodPanda App ================================\n\n";
    cout<<"Initialising....\n\n";

    Restaurants *rests = new Restaurants();
    CustomerHashTable *customers = new CustomerHashTable();

    cout<<"======== Menu ========\n";
    int choice;
    cin>>choice;
    switch(choice)
    {
        case 1:
            RestaurantWindow rWindow(rests);
            rWindow.menu();
        case 2:
            CustomerWindow cWindow(customers, rests);
            cWindow.menu();
    }

    delete rests;
    delete customers;


    return 0;
}