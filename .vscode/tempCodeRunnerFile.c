bool isRunning;
    while(isRunning == true){
        Menu();
        char *str[100];
        char option;
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
