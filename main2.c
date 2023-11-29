#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

/*

INT MAIN{ ------------THIS IS THE MAIN CONTROL OF ALL FUNCTIONS- 
    VOID DASHBOARD(){
        int LOGIN()
        int SIGNUP()
    }link to MENU when LOGIN

    VOID MENU{
        int MATH WHIZ()
        int LEADERBOARDS()
        void  ABOUT()
        char EXIT();
    }
}
*/

struct user{
    char username[50];
    char password[12];
    struct progress{
        char stage;
        char level;
    }mode[];
};

int signup(int registration_Auth){
    char password_checker[12], username_checker[50],file_name[50];
    struct user account;
    FILE *details;
    printf("\nEnter preferred username:\t");
    scanf("%s", &username_checker);
    printf("\nEnter preferred password:\t");
    scanf("%s", &account.password);
    printf("\nConfirm preferred password:\t");
    scanf("%s", &password_checker);
    strcpy(file_name,username_checker);
    details = fopen(strcat(file_name,".txt"),"w+");
    /*if(details == NULL){
        printf("USERNAME DOES NOT EXIST KAYA ACCOUNT REGISTRATION  SUCCESSFUL");
    }
    else{
        printf("\nUSERNAME ALREADY EXIST");
        getch(); 
    }*/
    if(!strcmp(account.password, password_checker)){
        fwrite(&account, sizeof(struct user),1, details);
        registration_Auth = 1;
        printf("\nSIGN UP SUCCESS");
        getch();
    }
    else{
        registration_Auth = 0;
        printf("\nPASSWORD DOES NOT MATCH");
        getch();
    }
    fclose(details);
return registration_Auth;
}
int login(int login_Auth)
{
    char password_checker[12],file_name[50];
    struct user account;
    FILE *details;
    printf("\nEnter preferred username:\t");
    scanf("%s", &account.username);
    printf("\nEnter preferred password:\t");
    scanf("%s", &account.password);
    strcpy(file_name, account.username);
    details = fopen(strcat(file_name,".txt"),"r");
    if(details == NULL) printf("\nACCOUNT DOES NOT EXIST");
    else{
        while(fread(&account, sizeof(struct user),1,details)!=EOF){
            if(!strcmp(account.password, password_checker)){
            login_Auth = 1;
            break;
            }
            else{
            printf("\nINCORRECT PASSWORD");
            login_Auth = 0;
            break;
            }
        }
    fclose(details);
    }

return login_Auth;   
}


void dashboard(){
    int signup_Auth= 0, login_Auth = 0;
    char option;
    dashboard:
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n[2] SIGN UP\n[3] EXIT");
    option = getch();
    option = toupper(option);
    switch(option){
        case 49 : //LOG IN FUNCTION // ASCII CODE OF [1] == 49
        system("cls");
        login_Auth = login(login_Auth);
        system("cls");
        break;

        case 50: //SIGN UP FUNCTION // ASCII CODE OF [2] == 50;  
        system("cls");
        signup_Auth = signup(signup_Auth);
        system("cls");
        goto dashboard;
        break;

        case 51 : return;

        default : system("cls");
        goto dashboard;
    }
}

void menu();
int math_whiz();
int leaderboards();
void about();

int main(){

    dashboard();

return 0;
}



