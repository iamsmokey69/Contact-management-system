#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;
void Menu();
void AddNewContact();
void ShowAllContacts();
void SearchContact();
void EditContact();
void DeleteContact();
void DeleteAllContacts();
void ClearWindow();
void PrintLineWithSpace(char *Name[20],char ContactInfo);
void ShowPhoneWithSpace(char *Phone[20]);
void ShowEmailWithSpace(char *Email[30]);
void ErrorAndRestart(char *error[100]);
bool AlreadyExists(char *GivenLine[30],char ContactInfo);
void GoBackOrExit();
void UserGuideline();
void AboutUs();
void Exit();

int main(){
        int i;
    cout<<"\t"<<"\t";
    char AppStarting[100] = "Application is Starting....";
    for(i=0;i<strlen(AppStarting);i++){
        cout<<AppStarting[i];
        Sleep(50);
    }    
    system("cls");
    bool isRunning;
    while(isRunning == true){
        Menu();
        char *str[100];
        char option;
        
        const char* str = "Option";
         option = str;
        scanf("%s",&str);
        option = str[0];
        switch(option){
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
ShowEmailWithSpace();

void AddNewContact(){
    printf("\n\t\t **** Add new Contact ****\n\n");
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewContact[100];
    NewContact[0] = 0;
    cout<<"Name Should be unique and maximum 20 character Long! "<<endl;
    cout<<"Enter Contact Name: ";
    cin>>Name;
}
    return 0;
}