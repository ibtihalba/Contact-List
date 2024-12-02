#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <climits>
#include <vector>


using namespace std;

//contact information format
struct Contact {
    string name;
    string phone;

    // Display contact details
    void display() const {
        cout << "  " << name << " : " << phone << endl;
    }
};

//contact list
vector<Contact> contacts;

// Search for a contact using contact name or phone number
void search_Contact() {
    string inp;
    cout << "Enter Contact Name or Phone to search: ";
    cin.ignore();
    getline(cin, inp);

    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.name == inp || contact.phone == inp) {
            contact.display();
            found = true;
        }
    }
    if (!found) {
        cout << "Contact not found.\n";
    }
}

// Function to add a contact
void add_Contact() {
    Contact newContact;
    cout << "Enter Contact  Name: ";
    cin.ignore();
    getline(cin, newContact.name);
    
    while (true) {
        cout << "Enter Phone Number(only digits accepted): ";
        cin >> newContact.phone;

        // Validate phone number contains digits only
        bool isValid = all_of(newContact.phone.begin(), newContact.phone.end(), ::isdigit);
        if (!isValid) {  
            cout << "Invalid input: Please enter digits only.\n";
            cin.clear(); 
            cin.ignore(INT_MAX, '\n');
        } else {
            break;
        }
    }
    contacts.push_back(newContact);
    cout << "Contact added successfully!\n";
}

//  Delete a contact
void delete_Contact() {
    string inp;
    cout << "Enter Contact Name: ";
    cin.ignore();
    getline(cin, inp);

    auto val = remove_if(contacts.begin(), contacts.end(), [&](const Contact& c) {
        return c.name == inp;
        });

    if (val != contacts.end()) {
        contacts.erase(val, contacts.end());
        cout << "Contact deleted successfully!\n";
    }
    else {
        cout << "Contact not found.\n";
    }
}

// edit a contact
void edit_Contact() {
    string inp;
    cout << "Enter Contact Name or Phone number to edit: ";
    cin.ignore();
    getline(cin, inp);

    bool found = false;
    for (auto &contact : contacts) {
        if (contact.name == inp) {
            found = true;
            cout << "Editing Contact:\n";
            contact.display();
            
            cout << "Enter new phone number (press Enter to keep the same): ";
            string newPhone;
            getline(cin, newPhone);
            if (!newPhone.empty()) {
                contact.phone = newPhone;
            }
            cout << "Contact updated successfully!\n";
            contact.display();
            break;
        }
    }

    if (!found) {
        cout << "Contact not found.\n";
    }
}


// Display all contacts
void list_Contacts() {
    if (contacts.empty()) {
        cout << " Empty contact list.\n";
        return;
    }
    cout << "Contact List:\n";
    for (const auto& contact : contacts) {
        contact.display();
    }
}

// Save contacts to a file
void save(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error message : Could not open file for writing.\n";
        return;
    }
    for (const auto& contact : contacts) {
        file << contact.name << "," << contact.phone << endl;
    }
    file.close();
    cout << "Contacts saved successfully!\n";
}

// Load contacts from a file
void load(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error message : Could not open file for reading.\n";
        return;
    }

    contacts.clear(); 
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            Contact contact;
            contact.name = line.substr(0, pos);
            contact.phone = line.substr(pos + 1);
            contacts.push_back(contact);
        }
    }
    file.close();
    cout << "Contacts loaded from file successfully!\n";
}

// main option list
void MenuDisplay() {
    cout << "1. List All Contacts\n";
    cout << "2. Search Contact\n";
    cout << "3. Add Contact\n";
    cout << "4. Edit Contact\n";
    cout << "5. Delete Contact\n";
    cout << "6. Save & Exit\n";
    cout << "Enter a number : ";
}

int main() {
    const string filename = "contacts.txt";

    // Load contacts from file 
    load(filename);

    while (true) {
        MenuDisplay();
        int option;
        cin >> option;

        switch (option) {
        case 1:
            list_Contacts();
            break;
        case 2:
            search_Contact();
            break;
        case 3:
            add_Contact();
            break;
        case 4:
            edit_Contact();
            break;
        case 5:
            delete_Contact();
            break;
        case 6:
            save(filename);
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Please try again the input is invalid.\n";
        }
    }

    return 0;
}
