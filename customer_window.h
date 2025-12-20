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
CustomerHashTable* c_hash;

public:
CustomerWindow(CustomerHashTable* c, Restaurants* r) {};

void menu(){};
};

#endif