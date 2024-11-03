#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void find_oldest_goat(const list<Goat> &trip);
void find_youngest_goat(const list<Goat> &trip);
void goat_search(const list<Goat> &trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Displaying the oldest goat.\n";
                find_oldest_goat(trip);
                break;
            case 5:
                cout << "Displaying the youngest goat.\n";
                find_youngest_goat(trip);
                break;
            case 6:
                cout << "Calculating average age.\n";
                find_average_age(trip);
                break;
            case 7:
                cout << "Search for a goat.\n";
                goat_search(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find the oldest goat\n";
    cout << "[5] Find the youngest goat\n";
    cout << "[6] Calculate average goat age\n";
    cout << "[7] Search of a goat\n";
    cout << "[8] \n";
    cout << "[9] \n";
    cout << "[10] \n";
    cout << "[11] \n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void find_oldest_goat(const list<Goat> &trip)
{
    auto oldest = max_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) { 
        return a.get_age() < b.get_age();
    });

    if(oldest != trip.end()){
        cout << "The oldest goat is: " << oldest->get_name() << "and is " << oldest->get_age() << " years old.\n";
    }
    else {
        cout << "No goats in the list.\n";
    }
}

void find_youngest_goat(const list<Goat> &trip)
{
    auto youngest = min_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) { 
        return a.get_age() < b.get_age();
    });

    if(youngest != trip.end()){
        cout << "The youngest goat is: " << youngest->get_name() << "and is " << youngest->get_age() << " years old.\n";
    }
    else {
        cout << "No goats in the list.\n";
    }
}

void goat_search(const list<Goat> &trip)
{
    string searchGoat;
    cout << "Which goat would you like to search for?: ";
    getline(cin, searchGoat);
    cout << endl;

    auto itSearch = find_if(trip.begin(), trip.end(), [searchGoat](const Goat &g) {
        return g.get_name() == searchGoat;
    });

    if (itSearch != trip.end())
        cout << "Found: " << itSearch->get_name() << " (Age: " << itSearch->get_age() << " , Color: " << itSearch->get_color() << ")\n";
    else
        cout << itSearch->get_name() << " not found.\n";

}