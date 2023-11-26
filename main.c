#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
/* 
--------------GUIDELINE AND OUTLINE OF PROGRAM-------------
--DASHBOARD{
    [1] LOGIN PAGE
    [2] SIGN UP PAGE
    [3] EXIT 
}

--MENU{
    [G] START MATH WHIZ
    [L] LEADERBOARDS
    [A] ABOUT MATH WHIZ
    [X] EXIT OPTION
}

--ABOUT MATH WHIZ{
    [B] BACK TO MENU OPTION
}

--LEADERBOARDS{
    [B] BACK TO MENU OPTION
    [X] EXIT OPTION
}

--MATH WHIZ{

    [X] EXIT OPTION
}
-----------------------------------------------------------
*/

struct user
{
    char username[20];
    char password[12];
};

//SIGNUP FUNCTION//
int signup(int isRegistered)
{   
    char confirm_password[12];
    struct user account;
    FILE *details_handler;
    isRegistered = 0;

    details_handler = fopen("account_details.txt","a");
    do{
    if(details_handler == NULL) printf("ERROR_FILE_NOT_FOUND_3"); 
    system("cls");
    printf("CREATE YOUR ACCOUNT");
    printf("\n\n\n");
    printf("Enter your username:\t");
    scanf("%s", &account.username);
    printf("Enter your password:\t");
    scanf("%s", &account.password);
    printf("Confirm your passsword:\t");
    scanf("%s", &confirm_password);
    if(!strcmp(account.password, confirm_password)){
        printf("\nACCOUNT CREATED\n");
        fwrite(&account, sizeof(struct user),1,details_handler);
        fclose(details_handler);
        
        getch();
        break;
    }
    else{
        printf("\nPassword doesn't match\n");
        getch();
    }
    }while(strcmp(account.password, confirm_password));

return isRegistered = 1;
}//END OF SIGNUP FUNCTION//

//LOGIN FUNCTION//
void login()
{
    char username_checker[20], password_checker[12];
    struct user account;
    FILE *details_checker;

    printf("CREATE YOUR ACCOUNT");
    printf("\n\n\n");
    printf("Username:\t");
    scanf("%s", username_checker);
    printf("Password:\t");
    scanf("%s", password_checker);
    details_checker = fopen("account_details.txt", "r");
    if(details_checker == NULL) 
    printf("ERROR_FILE_NOT_FOUND_3");
    else{//GANON PARIN PROBLEMA SA ACCOUNT: AUTHENTICATION ISSUE OF USERNAME AND PASSWORD IDENTIFIER SA FILE. 
        while(fread(&account.username, sizeof(struct user),1 ,details_checker)!=EOF){
            if(!strcmp(account.username, username_checker)){
                if(!strcmp(account.password, password_checker)){
                    printf("\nLOGIN SUCCESS");
                    break;
                }
                else{
                    printf("\nINVALID PASSWORD");
                    getch();
                    break;
                }
            }
            else{
                printf("\nINVALID USERNAME");
                getch();
                break;
            }
        }
    }
}
//END OF LOGIN FUNCTION//

int main()
{   
    int option_select, isRegistered = 0, auth = 0;
    char confirm_passsword[12];
    struct user account;

    //FILE *details_handler;
    //DASHBOARD PAGE//
    dashboard:
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n");
    printf("[2] SIGN UP\n");
    printf("[3] EXIT\n\n\n");
    printf("SELECT:\t");
    scanf("%i", &option_select);
    //END OF DASHBOARD PAGE//
    switch(option_select){
        case 1 : //LOG IN PAGE//
        system("cls");
        login();
        break;//END LOG IN PAGE//
        
        case 2 : //SIGN UP PAGE//
        system("cls");
        isRegistered = signup(isRegistered);
        break;//END OF SIGN UP PAGE//

        case 3 : //EXIT CODE
        return 1;
    }
    if(isRegistered== 1){
        system("cls");
        goto dashboard;
    }
return 0;
}