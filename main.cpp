#include <iostream>
using namespace std;

#include "admin.h"

class Application
{
private:
    void initialise()
    {
        cout << "Initialising system..." << endl;
    };

    void MainMenu()
    {
        initialise();
        cout << endl
             << "======================== FoodPanda App ========================" << endl
             << endl;
        cout << "Main Menu: " << endl;
        cout << "\t1. Customer Login" << endl;
        cout << "\t2. Restaurant Login" << endl;
        cout << "\t3. Delivery Personnel Login" << endl;
        cout << "\t4. Admin Login" << endl;
        cout << "\t5. Exit Application" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Customer Login selected." << endl;
            // Call Customer Login function here
            break;
        case 2:
            cout << "Restaurant Login selected." << endl;
            // Call Restaurant Login function here
            break;
        case 3:
            cout << "Delivery Personnel Login selected." << endl;
            // Call Delivery Personnel Login function here
            break;
        case 4:
        {
            Admin adminPanel;
            adminPanel.adminWindow();
            break;
        }
        case 5:
            cout << "Exiting application. Goodbye!" << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            MainMenu(); // Re-display the menu for invalid choice
            break;
        }
    };

public:
    Application() {
    };

    void run()
    {
        while (true)
        {
            MainMenu();
        }
    };
};

int main()
{
    Application app;
    app.run();
    return 0;
}