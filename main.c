#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
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
    char progress[12];
};

//SIGNUP FUNCTION//
int signup(int isRegistered)
{   
    char option, username_checker[20], confirm_password[12], file_name[FILENAME_MAX];
    struct user account;
    FILE *details_handler;
    isRegistered = 0;

    tryagain:
    system("cls");
    printf("CREATE YOUR ACCOUNT");
    printf("\n\n\n");
    printf("Enter your username:\t");
    scanf("%s", &username_checker);
    printf("Enter your password:\t");
    scanf("%s", &account.password);
    printf("Confirm your passsword:\t");
    scanf("%s", &confirm_password);
    strcpy(file_name, username_checker); 

    details_handler = fopen(strcat(file_name,".txt"),"w+");
    if(details_handler == NULL) printf("ERROR_FILE_NOT_FOUND_3");
    if(!strcmp(account.username, username_checker)){
        printf("\nUSERNAME HAVE ALREADY EXIST!\n");
        fclose(details_handler);
        getch();
        return isRegistered;
        
    }
    else{
        if(!strcmp(account.password, confirm_password)){
            fwrite(&account, sizeof(struct user),1,details_handler);
            fclose(details_handler);
            isRegistered=1;
            printf("\nAccount has been created successfully\nPress any key to continue");
            getch();
        }
        else{
            printf("\nPASSWORD DOES NOT MATCH\n\nPress Y to try again\nPress B to go back to dashboard");
            option = getch();
            if(option == 121 || option == 89 ){
                goto tryagain;
            }
            else if(option == 98 || option == 66){
                return isRegistered = 0;
            }
        }
    }

return isRegistered;
}//END OF SIGNUP FUNCTION//

//LOGIN FUNCTION//
int login(int isLogin)
{
    
    isLogin=0;
    int isUsername_exist, isPassword_exist;
    char username_checker[20], password_checker[12], file_name[FILENAME_MAX];
    struct user account;
    FILE *details_handler;

    printf("LOGIN INTO YOUR ACCOUNT");
    printf("\n\n\n");
    printf("Username:\t");
    scanf("%s", username_checker);
    printf("Password:\t");
    scanf("%s", password_checker);
    strcpy(file_name,username_checker);
    details_handler = fopen(strcat(file_name,".txt"), "r");
    if(details_handler == NULL) printf("\nACCOUNT DOES NOT EXIST\n");
    else{
        while(fread(&account, sizeof(struct user),1, details_handler)!=EOF){
            if(!strcmp(account.password, password_checker)){
            isLogin = 1;
            break;
            }
            else{
            printf("\nINCORRECT PASSWORD");
            isLogin=0;
            break;
            }
        }
        fclose(details_handler);
    }
return isLogin;
}
//END OF LOGIN FUNCTION//

int about(char about_option)
{   
    printf("MATH WHIZ ABOUT");
    printf("\n\n\n\n\n\n");
    printf("Press [B] to go back to menu");
    about_option = getch();
    about_option = toupper( about_option);
    if(about_option == 66){
    return  about_option;
    }
}


int menu(char menu_option)
{
    tryagain:
    printf("MATH WHIZ");
    printf("\n\n\n");
    printf("[G] START\n[L] LEADERBOARDS\n[A] ABOUT PAGE\n[X] EXIT");
    menu_option = getch();
    menu_option = toupper(menu_option);
    switch(menu_option){
        case 71 : printf("THIS IS MATH WHIZ PAGE");
        break;
                
        case 76 : printf("L: THIS IS LEADERBOARDS PAGE");
        break;
                
        case 65 : printf("A: THIS IS ABOUT PAGE");
        break;
                
        case 88 : printf("X: THIS EXIT BUTTON");
        break;
        
        default : system("cls"); 
        goto tryagain;
    }
return menu_option;
}



int main()
{   
    int isRegistered = 0, auth = 0;
    char dashboard_select, confirm_passsword[12], menu_option;
    struct user account;

    //FILE *details_handler;
    //DASHBOARD PAGE//
    dashboard:
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n[2] SIGN UP\n[3] EXIT\n\n\n");
    printf("PRESS THE CORRESPONDING KEY TO SELECT");
    dashboard_select = getch();
    //END OF DASHBOARD PAGE//
    if(dashboard_select == 49){//LOG IN PAGE FUNCTION//
        system("cls");
        auth = login(auth);
        if(auth==0){
            getch();
            system("cls");
            goto dashboard;
        }
        else if(auth == 1){
            system("cls");
            menu_option = menu(menu_option);//MENU PAGE FUNCTION//
            
        }
    }//END LOG IN PAGE FUNCTION//
    else if(dashboard_select == 50){
        //SIGN UP PAGE FUNCTION//
        system("cls");
        isRegistered = signup(isRegistered);
        if(isRegistered==1){
        system("cls");
        goto dashboard;
        }
        //END OF SIGN UP PAGE FUNCTION//
    }
    else if(dashboard_select == 51){
        //EXIT CODE
        return 1;
    }
    else{
        printf("\nINVALID KEY SELECTION\n");
        getch();
        system("cls");
        goto dashboard;
    }
return 0;
}

void dashboard()
{
    printf("MATH WHIZ");
    printf("\n\n\n");
    printf("[1]\nLOG IN[2]\nSIGN UP[3]EXIT");
}