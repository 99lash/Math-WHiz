#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
//RERECONSTRUCT KO KASI HINDI NA READABLE YUNG REAL MAIN
struct user{
    char username[20],
         password[12];
    struct progress{
    int stages[6],
        levels[5];
    }mode;
};

void signup();
void login();
void menu();
void math_whiz();
void about();
void leaderboards();

int main(){

    char option;
    //dashboard//
    while(option != 49 && option != 50 && option != 51){ //ASCII CODE [1] is 49, [2] is 50, [3] is 51//
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n[2] SIGN UP\n[3] EXIT\n");
    option = getch();
    option = toupper(option);
        switch(option){
            case 49 : system("cls"); printf("LOG IN"); break;
            case 50 : system("cls"); printf("SIGN UP"); break;
            case 51 : system("cls"); printf("EXIT "); break;
            default : system("cls"); continue;
        }
    }
return 0;
}

void signup(){
    char username_checker[20], password_checker[12], file_name[20];
    struct user account;
    FILE *details;
    
    printf("SIGN UP\n\n\n");
    printf("Enter preferred username:\t");
    scanf("%s", username_checker);
    printf("Enter preferred password:\t");
    scanf("%s", account.password);
    printf("Repeat preferred username:\t");
    scanf("%s", password_checker);
    details = fopen("usernames.txt", "a+");
    strcpy(file_name, username_checker);
}