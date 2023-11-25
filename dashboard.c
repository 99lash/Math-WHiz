#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
//#include <time.h> wala pang math whiz main

struct user{
    char username[20];
    char password [12];
};

struct user_progress{
    int stage;
    int level;
};

void title()
{
printf("Math Whiz");
printf("\n\n\n\n\n");
}

int main()
{

    int select, decision=0;
    char confirm_password[12], iUsername[20], iPassword[12];
    FILE *f1;
    struct user account;

    dashboard:
    do{
    title();
    printf("\n");
    printf("[1] CREATE\n");
    printf("[2] LOG IN \n");
    printf("[3] ABOUT MATH WHIZ\n");
    printf("[4] EXIT");
    printf("\n\n\n\n\n");
    printf("Select :\t");
    scanf("%i", &select);
    
    switch(select){
        
        case 1 : //REGISTER
        system("CLS");
        retry_loop:
        f1 = fopen("account_details.txt", "a+");
        if(f1 == NULL) printf("\nFILE NOT FOUND\n");
        //while(fread(&account.username, sizeof(struct user),1 ,f1)!=EOF){
        printf("\nEnter preferred username:\t");
        scanf("%s", &account.username);
        //}
        printf("\nEnter preferred password:\t");
        scanf("%s", &account.password);
        printf("\nRe-enter preferred password:\t");
        scanf("%s", &confirm_password);
        if(!strcmp(account.password, confirm_password)){
            printf("Account Created\n");
            fwrite(&account, sizeof(struct user), 1, f1);
            //fprintf(f1, "%s", &account.username);
            //fprintf(f1, "%s\n", &account.password);

        }
        else{
            system("CLS");
            goto retry_loop;
        }
        fclose(f1);
        getch();
        system("CLS");
        break;

        case 2: //LOG IN
        system("CLS");
        printf("Username:\t");
        scanf("%s", &iUsername);
        printf("Password:\t");
        scanf("%s", &iPassword);
        f1 = fopen("account_details.txt", "rb");
        if(f1 == NULL) printf("\nFILE NOT FOUND\n");
        while(fread(&account, sizeof(struct user),1, f1)!=EOF){
        //while(fscanf(f1, "%s", &account.username)!=EOF){
        //fscanf(f1, "%s", &account.password);
            if(!strcmp(account.username, iUsername)){
                if(!strcmp(account.password, iPassword)){
                printf("A1\n");
                decision=1;
                break;
                }
                else
                    printf("A\n");
                break;
            }
            else{
                printf("B\n");
                goto dashboard;
            }
        }
        if(decision != 0){
        printf("\nLOGIN SUCCESSFUL\nClick any key to continue");
        getch();
        decision = 0;
        select = 5;
        fclose(f1);
        system("CLS");
        }
        else if(decision == 0){
        printf("\nINVALID CREDENTIALS\nClick any key to continue");
        fclose(f1);
        getch();
        system("CLS");
        }
        else{
        printf("SOMETHING WENT ERROR!");
        fclose(f1);
        getch();
        system("CLS");
        }
        break;

        case 3: //ABOUT MATH WHIZ
        system("CLS");
        printf("MATH WHIZ ABOUT");
        printf("\n\n\n\n\n\n");
        printf("PRESS ANY KEY TO GO BACK");
        getch();
        system("CLS");
        goto dashboard;
    }
    }while(select!=4);
    system("CLS");
return 0;
}