#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

bool isRunning = true;

void Menu();
void AddNewContact();
void ShowAllContacts();
void SearchContact();
void EditContact();
void DeleteContact();
void DeleteAllContacts();
void ClearWindow();
void PrintLineWithSpace(const string &Name, char ContactInfo);
void ShowPhoneWithSpace(const string &Phone);
void ShowEmailWithSpace(const string &Email);
void ErrorAndRestart(const string &error);
bool AlreadyExists(const string &GivenLine, char ContactInfo);
void GoBackOrExit();
void UserGuideline();
void AboutUs();
void Exit();


int main() {
    srand(time(0));

    int i;
    cout << "\t\t";
    string AppStarting = "Application is Starting....";
    for (i = 0; i < AppStarting.length(); i++) {
        cout << AppStarting[i];
        Sleep(40);
    }
    system("cls");

    while (isRunning) {
        Menu();
        string option;
        cin >> option;
        char choice = option[0];
        switch (choice) {
            case '0':
                Exit();
                break;
            case '1':
                AddNewContact();
                break;
            case '2':
                ShowAllContacts();
                break;
            case '3':
                SearchContact();
                break;
            case '4':
                EditContact();
                break;
            case '5':
                DeleteContact();
                break;
            case '6':
                DeleteAllContacts();
                break;
            case '7':
                system("cls");
                break;
            case 'I':
            case 'i':
                UserGuideline();
                break;
            case 'A':
            case 'a':
                AboutUs();
                break;
            default:
                ErrorAndRestart("Option not found!");
                break;
        }
    }

    return 0;
}

void Menu() {
    cout << "\n\t **** My-Contact Management System Using C++ ****\n";
    cout << "\n\t\t\tMAIN MENU\n";
    cout << "\t\t=====================\n";
    cout << "\t\t[1] Add a new Contact\n";
    cout << "\t\t[2] Show all Contacts\n";
    cout << "\t\t[3] Search for contact\n";
    cout << "\t\t[4] Edit a Contact\n";
    cout << "\t\t[5] Delete a Contact\n";
    cout << "\t\t[6] Delete All Contact\n";
    cout << "\t\t[7] Clear Window\n";
    cout << "\t\t[i] User Guideline\n";
    cout << "\t\t[a] About Us\n";
    cout << "\t\t[0] Exit\n\t\t=================\n\t\t";
    cout << "Enter the choice: ";
}

void AddNewContact() {
    system("cls");
    cout << "\n\t\t **** Add new Contact ****\n\n";
    
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewContact[100];
    NewContact[0] = 0;

    cout << "*Name should be unique and maximum 20 characters long.\n";
    cout << "Enter The Name: ";
    cin.ignore(); 
    cin.getline(Name, 20);

    if (strlen(Name) > 20) {
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    if (AlreadyExists(Name, 'n')) {
        ErrorAndRestart("!!!!Name Already Exists!!!");
        return;
    }

    cout << "\n*Phone should be unique and maximum 20 characters long.\n";
    cout << "Enter The Phone Number: ";
    cin.getline(Phone, 20);

    if (strlen(Phone) > 20) {
        ErrorAndRestart("!!!!Phone Length Error!!!!");
        return;
    }

    if (AlreadyExists(Phone, 'p')) {
        ErrorAndRestart("!!!!Phone Number Already Exists!!!");
        return;
    }

    cout << "\n*Email should be unique and maximum 30 characters long.\n";
    cout << "Enter The Email: ";
    cin.getline(Email, 30);

    if (strlen(Email) > 30) {
        ErrorAndRestart("!!!!Email Length Error!!!!");
        return;
    }

    if (AlreadyExists(Email, 'e')) {
        ErrorAndRestart("!!!!Email Already Exists!!!");
        return;
    }

    strcat(NewContact, Name);
    strcat(NewContact, "\n");
    strcat(NewContact, Phone);
    strcat(NewContact, "\n");
    strcat(NewContact, Email);
    strcat(NewContact, "\n");

    ofstream allContactTxtFile("All-Contact.txt", ios::app);
    allContactTxtFile << NewContact;
    allContactTxtFile.close();

    cout << "\nContact Added Successfully!\n";
    GoBackOrExit();
}

void ShowAllContacts() {
    system("cls");
    cout << "\n\t\t **** All Contacts ****\n\n";

    ifstream AllContactTextFile("All-Contact.txt");
    int LineLength = 300;
    char Line[LineLength];

    cout << "|====================|====================|==============================|\n";
    cout << "|        Name        |    Phone Number    |          Email               |\n";
    cout << "|====================|====================|==============================|\n";

    int TotalContact = 0;
    int LineCount = 0;

    while (AllContactTextFile.getline(Line, LineLength)) {
        LineCount++;

        if (LineCount == 1) {
            PrintLineWithSpace(Line, 'n');
        }
        else if (LineCount == 2) {
            PrintLineWithSpace(Line, 'p');
        }
        else if (LineCount == 3) {
            PrintLineWithSpace(Line, 'e');
            LineCount = 0;
            TotalContact++;
        }
    }

    cout << "|====================|====================|==============================|\n";
    cout << "You Have Total " << TotalContact << " Contacts.\n\n";
    AllContactTextFile.close();
    GoBackOrExit();
}

void SearchContact() {
    system("cls");
    cout << "\n\t\t **** Search Contact ****\n\n";

    int FoundContact = 0;
    string GivenName;
    cout << "*Name should be maximum 20 characters long.\n";
    cout << "Enter The Name: ";
    cin.ignore(); 
    getline(cin, GivenName);

    if (GivenName.length() > 20) {
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    GivenName += "\n";

    ifstream AllContactFile("All-Contact.txt");
    int LineLength = 255;
    char Line[LineLength];
    int LineCount = 0;
    int NeedToPrintLine = 0;

    while (AllContactFile.getline(Line, LineLength)) {
        LineCount++;

        if (LineCount == 1 && GivenName == Line) {
            FoundContact = 1;
            NeedToPrintLine = 3;
        }

        if (NeedToPrintLine > 0) {
            if (LineCount == 1) {
                cout << "\nContact information of " << GivenName;
                cout << "Name: " << Line;
                NeedToPrintLine = 2;
            }
            else if (LineCount == 2) {
                cout << "Phone: " << Line;
                NeedToPrintLine = 1;
            }
            else if (LineCount == 3) {
                cout << "Email: " << Line << endl;
                NeedToPrintLine = 0;
            }
        }

        if (LineCount == 3) {
            LineCount = 0;
        }
    }

    AllContactFile.close();

    if (FoundContact == 0) {
        cout << "\nSorry, no contact found for " << GivenName;
    }

    GoBackOrExit();
}
void EditContact() {
    system("cls");
    cout << "\n\t\t **** Edit Contact ****\n\n";

    int LineCount = 0;
    int FoundContact = 0;
    int SkipLines = 0;
    string GivenName2;
    string NewName;
    string NewPhone;
    string NewEmail;
    string NewFullContact;
    NewFullContact = "";

    cout << "*Name should be maximum 20 characters long.\n";
    cout << "Enter The Name of the contact you want to edit: ";
    cin.ignore();
    getline(cin, GivenName2);

    if (GivenName2.length() > 20) {
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    GivenName2 += "\n";

    ifstream OurExistingFile("All-Contact.txt");
    ofstream NewTempFile("temp-file.txt");

    int LineLength = 255;
    char Line[LineLength];

    while (OurExistingFile.getline(Line, LineLength)) {
        LineCount++;

        if (LineCount == 1 && GivenName2 == Line) {
            FoundContact = 1;
            SkipLines = 3;
        }

        if (SkipLines > 0) {
            if (LineCount == 1) {
                cout << "\n*New Name should be unique and maximum 20 characters long.\n";
                cout << "Old Name is: " << Line;
                cout << "New Name (0 to skip): ";
                getline(cin, NewName);

                if (NewName == "0") {
                    NewFullContact += Line;
                }
                else {
                    if (NewName.length() > 20) {
                        ErrorAndRestart("!!!!Name Length Error!!!");
                        return;
                    }
                    if (AlreadyExists(NewName, 'n')) {
                        ErrorAndRestart("!!!!Name Already Exists!!!");
                        return;
                    }
                    NewFullContact += NewName + "\n";
                }
                SkipLines = 2;
            }
            else if (LineCount == 2) {
                cout << "\n*New Phone should be unique and maximum 20 characters long.\n";
                cout << "Old Phone is: " << Line;
                cout << "New Phone (0 to skip): ";
                getline(cin, NewPhone);

                if (NewPhone == "0") {
                    NewFullContact += Line;
                }
                else {
                    if (NewPhone.length() > 20) {
                        ErrorAndRestart("!!!!Phone Length Error!!!");
                        return;
                    }
                    if (AlreadyExists(NewPhone, 'p')) {
                        ErrorAndRestart("!!!!Phone Already Exists!!!");
                        return;
                    }
                    NewFullContact += NewPhone + "\n";
                }
                SkipLines = 1;
            }
            else if (LineCount == 3) {
                cout << "\n*New Email should be unique and maximum 30 characters long.\n";
                cout << "Old Email is: " << Line;
                cout << "New Email (0 to skip): ";
                getline(cin, NewEmail);

                if (NewEmail == "0") {
                    NewFullContact += Line;
                }
                else {
                    if (NewEmail.length() > 30) {
                        ErrorAndRestart("!!!!Email Length Error!!!");
                        return;
                    }
                    if (AlreadyExists(NewEmail, 'e')) {
                        ErrorAndRestart("!!!!Email Already Exists!!!");
                        return;
                    }
                    NewFullContact += NewEmail + "\n";
                }
                SkipLines = 0;
                NewTempFile << NewFullContact;
            }
        }
        else {
            NewTempFile << Line;
        }

        if (LineCount == 3) {
            LineCount = 0;
        }
    }

    NewTempFile.close();
    OurExistingFile.close();

    if (FoundContact == 0) {
        cout << "Contact Not Found!\n";
        remove("temp-file.txt");
    }
    else {
        cout << "\nContact Updated Successfully!\n\n";
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }

    GoBackOrExit();
}

void DeleteContact() {
    system("cls");
    cout << "\n\t\t **** Delete Contact ****\n\n";

    int LineCount = 0;
    int FoundTheContact = 0;
    int SkipLines = 0;
    string GivenName;

    cout << "*Name should be maximum 20 characters long.\n";
    cout << "Enter The Name of the contact you want to delete: ";
    cin.ignore(); 
    getline(cin, GivenName);

    if (GivenName.length() > 20) {
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    GivenName += "\n";

    ifstream OurExistingFile("All-Contact.txt");
    ofstream NewTempFile("temp-file.txt");

    int LineLength = 300;
    char Line[LineLength];

    while (OurExistingFile.getline(Line, LineLength)) {
        LineCount++;

        if (LineCount == 1 && GivenName == Line) {
            FoundTheContact = 1;
            SkipLines = 3;
        }

        if (SkipLines > 0) {
            SkipLines--;
        } else {
            NewTempFile << Line << endl;
        }

        if (LineCount == 3) {
            LineCount = 0;
        }
    }

    OurExistingFile.close();
    NewTempFile.close();

    if (FoundTheContact == 0) {
        cout << "\nContact Not Found!\n\n";
        remove("temp-file.txt");
    } else {
        cout << "\nContact Deleted Successfully!\n\n";
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }

    GoBackOrExit();
}

void DeleteAllContacts() {
    system("cls");
    cout << "\n\t\t **** Delete All The Contacts ****\n\n";

    char Option;
    cin.ignore(); 
    cout << "Are you sure you want to delete all the contacts? (Y/N)?: ";
    cin >> Option;

    if (Option == 'Y' || Option == 'y') {
        remove("All-Contact.txt");
        ofstream AllContactTxtFile("All-Contact.txt");
        AllContactTxtFile.close();

        const char Deleting[] = "Deleting....";
        for (int i = 0; Deleting[i] != '\0'; i++) {
            cout << Deleting[i];
            Sleep(40);
        }
        cout << "\nSuccessfully Deleted All Contacts!\n\n";
    }

    GoBackOrExit();
}
void ClearWindow() {
    system("cls");
    Menu(); 
}
void PrintLineWithSpace(const string &Name, char ContactInfo) {
    int i;
    string FormatedName = Name;
    int FormatedNameLength = FormatedName.length();

    int TotalSpace = 0;
    if (ContactInfo == 'n') {
        TotalSpace = 20 - FormatedNameLength;
    }
    else if (ContactInfo == 'p') {
        TotalSpace = 20 - FormatedNameLength; 
    }
    else if (ContactInfo == 'e') {
        TotalSpace = 30 - FormatedNameLength; 
    }

    cout << "|";
    for (i = 0; i < FormatedNameLength; i++) {
        cout << FormatedName[i];
    }

    for (i = 0; i <= TotalSpace; i++) {
        cout << " ";
    }

    if (ContactInfo == 'e') {
        cout << "|\n";
        cout << "|--------------------|--------------------|------------------------------|\n";
    }
}

void ShowPhoneWithSpace(const string &Phone) {
    int i;
    string FormatedPhone = Phone;
    int FormatedPhoneLength = FormatedPhone.length();

    int TotalSpace = 20 - FormatedPhoneLength;

    cout << "|";
    for (i = 0; i < FormatedPhoneLength; i++) {
        cout << FormatedPhone[i];
    }

    for (i = 0; i <= TotalSpace; i++) {
        cout << " ";
    }

    cout << "|";
}
void ShowEmailWithSpace(const string &Email) {
    int i;
    string FormatedEmail = Email;
    int FormatedEmailLength = FormatedEmail.length();

    int TotalSpace = 30 - FormatedEmailLength;

    cout << "|";
    for (i = 0; i < FormatedEmailLength; i++) {
        cout << FormatedEmail[i];
    }

    for (i = 0; i <= TotalSpace; i++) {
        cout << " ";
    }

    cout << "|\n";
    cout << "|====================|====================|==============================|\n";
}

void ErrorAndRestart(const string &error) {
    cout << error << endl;
    cout << "Restarting the program: ";
    for (int i = 0; i < 10; i++) {
        cout << ".";
        Sleep(500); 
    }
    system("cls");
    main(); 
}

bool AlreadyExists(const string &GivenLine, char ContactInfo) {
    string ThisLine = GivenLine + "\n";
    int FileLineNumber = 0;
    
    if (ContactInfo == 'n') {
        FileLineNumber = 1;
    } else if (ContactInfo == 'p') {
        FileLineNumber = 2;
    } else if (ContactInfo == 'e') {
        FileLineNumber = 3;
    }

    ifstream AllContactFile("All-Contact.txt");
    int LineLength = 255;
    char Line[LineLength];
    int LineCount = 0;
    bool Found = false;

    while (AllContactFile.getline(Line, LineLength)) {
        LineCount++;

        if (LineCount == FileLineNumber && ThisLine == Line) {
            Found = true;
            break;
        }

        if (LineCount == 3) {
            LineCount = 0;
        }
    }

    AllContactFile.close();
    return Found;
}

void GoBackOrExit() {
    char option;
    cin.ignore();
    cout << "Go Back(b)? or Exit(0)? ";
    cin >> option;

    if (option == '0') {
        Exit();
    } else {
        system("cls");
        Menu();
    }
}

void UserGuideline() {
    system("cls");
    cout << "\n\t\t **** User Guidelines ****\n\n";
    cout << "1. Use the provided options to navigate the program.\n";
    cout << "2. Follow the prompts to add, view, edit, or delete contacts.\n";
    cout << "3. Make sure to provide accurate and unique information for each contact.\n";
    cout << "4. Use 'Clear Window' option to clear the screen.\n";
    cout << "5. Use 'Exit' option to quit the program.\n";
    cout << "\nPress any key to go back to the main menu...\n";
    
    cin.ignore();
    cin.get();
    Menu();
}
void AboutUs() {
    system("cls");
    cout << "\n\t\t **** My-Contact Management System ****\n";
    cout << "\n\n\n\t\t\tAbout Us\n";
    cout << "\t\t======================\n";
    cout << "\t\t[i] This program is managed by Prashant Dwivedi\n";
    cout << "\t\t[i] Prashant is constantly learning and improving his coding skills\n";
    cout << "\t\t[>] He is passionate about computer programming and technology\n";
    cout << "\t\t======================\n\t\t";
    
    GoBackOrExit();
}
void Exit() {
    cin.ignore(); 
    cout << "Are You Sure You Want to Exit? (Y/N): ";
    char YesOrNo;
    cin >> YesOrNo;

    if (YesOrNo == 'Y' || YesOrNo == 'y') {
        system("cls");
        cout << "Visit www.CodeCartBd.com for more." << endl;
        cout << "Visit www.insideTheDiv.com for more." << endl;

        const char ThankYou[] = "===== Thank You =====\n";
        const char SeeYouSoon[] = "===== See You Soon =====\n";

        for (int i = 0; ThankYou[i] != '\0'; i++) {
            cout << ThankYou[i];
            Sleep(40);
        }
        for (int i = 0; SeeYouSoon[i] != '\0'; i++) {
            cout << SeeYouSoon[i];
            Sleep(40);
        }

        isRunning = false;
    }
}
