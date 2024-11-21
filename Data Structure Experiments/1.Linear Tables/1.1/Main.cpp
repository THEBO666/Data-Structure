// #include "Sqlist.hpp"
// #include "LinkList.hpp"
// #include <iostream>
// #include <list>
// std::list<int> l;

// int main()
// {
//     /*Sqlist<int> sq;
//     sq.InitSqlist();
//     sq.push_back(1);
//     sq.push_back(2);
//     sq.push_back(3);
//     sq.push_back(4);
//     sq.push_back(5);
//     sq.push_back(6);
//     sq.push_back(9);
//     sq.insert(6,999);
//     sq.erase(7);
//     for(int i=0;i<sq.size();i++)
//     {
//         std::cout<<sq[i]<<" ";
//     }
//     std::cout<<sq.find(6);*/

//     LinkList<int> lt;
//     lt.push_back(1);
//     lt.push_back(10);
//     lt.push_back(99);
//     lt.push_back(25);
//     lt.push_back(36);
//     lt.push_back(52);
//     lt.push_back(21);
//     lt.push_back(78);
//     lt.PrintList();
//     lt.insert(0,2);
//     lt.push_front(10);
//     lt.push_front(11);
//     lt.push_front(12);
//     lt.push_front(13);
//     lt.push_front(14);
//     lt.push_front(15);
//     lt.push_front(16);
//      lt.erase(0);
//      lt.erase(0);
//      lt.erase(0);
//      lt.erase(0);
//     lt.PrintList();
   
//     std::cout<<lt.size();
//     return 0;
// }
#include <iostream>
#include <cstdlib>
#include "LinkList.hpp"
#include "Sqlist.hpp"

using namespace std;

// Function to display the menu
void displayMenu(const string& listType) {
    cout << "================ Linear Table (" << listType << ") Operations Menu ================\n";
    cout << "1. Push Back\n";
    cout << "2. Push Front\n";
    cout << "3. Insert at Position\n";
    cout << "4. Find Element\n";
    cout << "5. Erase Element at Position\n";
    cout << "6. Pop Back\n";
    cout << "7. Access Element at Index\n";
    cout << "8. Print the List\n";
    cout << "9. Get Size\n";
    cout << "10. Clear the List\n";
    cout << "11. Switch List Type\n";
    cout << "0. Exit\n";
    cout << "===============================================================================\n";
    cout << "Please enter your choice: ";
}

int main() {
    LinkList<int> linkedList;
    Sqlist<int> seqList;
    seqList.InitSqlist();

    int listChoice;
    cout << "Welcome to the Linear Table Operations Program!\n";
    cout << "Please select the type of linear table you want to use:\n";
    cout << "1. Linked List\n";
    cout << "2. Sequential List\n";
    cout << "Please enter your choice: ";
    cin >> listChoice;

    while (listChoice != 1 && listChoice != 2) {
        cout << "Invalid choice. Please select 1 or 2: ";
        cin >> listChoice;
    }

    bool exitProgram = false;
    int choice;
    while (!exitProgram) {
        string currentListType = (listChoice == 1) ? "Linked List" : "Sequential List";
        displayMenu(currentListType);
        cin >> choice;

        switch (choice) {
            case 1: { // Push Back
                int value;
                cout << "Enter the value to push back: ";
                cin >> value;
                if (listChoice == 1) {
                    linkedList.push_back(value);
                } else {
                    seqList.push_back(value);
                }
                cout << "Element pushed back successfully.\n";
                break;
            }
            case 2: { // Push Front
                int value;
                cout << "Enter the value to push front: ";
                cin >> value;
                if (listChoice == 1) {
                    linkedList.push_front(value);
                    cout << "Element pushed to front successfully.\n";
                } else {
                    cout << "Sequential List does not support push_front operation.\n";
                }
                break;
            }
            case 3: { // Insert at Position
                size_t pos;
                int value;
                cout << "Enter the position to insert at (starting from 0): ";
                cin >> pos;
                cout << "Enter the value to insert: ";
                cin >> value;
                size_t sz = (listChoice == 1) ? linkedList.size() : seqList.size();
                if (pos > sz) {
                    cout << "Invalid position. Position must be between 0 and " << sz << ".\n";
                    break;
                }
                if (listChoice == 1) {
                    linkedList.insert(pos, value);
                } else {
                    seqList.insert(pos, value);
                }
                cout << "Element inserted successfully.\n";
                break;
            }
            case 4: { // Find Element
                int value;
                cout << "Enter the value to find: ";
                cin >> value;
                size_t pos;
                if (listChoice == 1) {
                    pos = linkedList.find(value);
                } else {
                    pos = seqList.find(value);
                }
                if (pos != 0) {
                    cout << "Element found at position " << pos - 1 << ".\n";
                } else {
                    cout << "Element not found in the list.\n";
                }
                break;
            }
            case 5: { // Erase Element at Position
                size_t pos;
                cout << "Enter the position to erase (starting from 0): ";
                cin >> pos;
                size_t sz = (listChoice == 1) ? linkedList.size() : seqList.size();
                if (pos >= sz) {
                    cout << "Invalid position. Position must be between 0 and " << sz - 1 << ".\n";
                    break;
                }
                if (listChoice == 1) {
                    linkedList.erase(pos);
                } else {
                    seqList.erase(pos);
                }
                cout << "Element erased successfully.\n";
                break;
            }
            case 6: { // Pop Back
                size_t sz = (listChoice == 1) ? linkedList.size() : seqList.size();
                if (sz == 0) {
                    cout << "List is empty. Cannot pop back.\n";
                    break;
                }
                if (listChoice == 1) {
                    linkedList.pop_back();
                } else {
                    seqList.pop_back();
                }
                cout << "Last element popped successfully.\n";
                break;
            }
            case 7: { // Access Element at Index
                size_t index;
                cout << "Enter the index to access (starting from 0): ";
                cin >> index;
                size_t sz = (listChoice == 1) ? linkedList.size() : seqList.size();
                if (index >= sz) {
                    cout << "Index out of bounds. Valid indices are between 0 and " << sz - 1 << ".\n";
                    break;
                }
                if (listChoice == 1) {
                    cout << "Element at index " << index << " is " << linkedList[index] << ".\n";
                } else {
                    cout << "Element at index " << index << " is " << seqList[index] << ".\n";
                }
                break;
            }
            case 8: { // Print the List
                cout << "Current List: ";
                if (listChoice == 1) {
                    linkedList.PrintList();
                } else {
                    for (size_t i = 0; i < seqList.size(); ++i) {
                        cout << seqList[i] << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 9: { // Get Size
                size_t sz = (listChoice == 1) ? linkedList.size() : seqList.size();
                cout << "Current size of the list is " << sz << ".\n";
                break;
            }
            case 10: { // Clear the List
                if (listChoice == 1) {
                    linkedList.clear();
                } else {
                    //seqList.clear();
                }
                cout << "List cleared successfully.\n";
                break;
            }
            case 11: { // Switch List Type
                listChoice = (listChoice == 1) ? 2 : 1;
                cout << "Switched to " << ((listChoice == 1) ? "Linked List" : "Sequential List") << ".\n";
                break;
            }
            case 0: { // Exit
                exitProgram = true;
                cout << "Exiting the program. Goodbye!\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << endl;
    }
    return 0;
}
