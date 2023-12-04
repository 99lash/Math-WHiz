#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

int counter=0;

struct user{
    char username[20], password[12];
    int stage;
};
//PROTOTYPE FUNCTIONS OF SYSTEM OUTLINE/GUIDELINES FLOW
void signup();
void login();
void menu();
void math_whiz();
void about();
void leaderboards();

//Function of Operators
int addition(int n1, int n2) {return n1 + n2;}
int subtraction(int n1, int n2) { return n1 - n2; }
int multiplication(int n1, int n2) { return n1 * n2; }
float division(float n1, float n2) { return n1 / n2; }
//Function of Mixed Operators
int addandsub(int n1, int n2, int n3) { return n1 + n2 - n3; }
float mulanddiv(float n1, float n2, float n3) { return n1 * n2 / n3; }
float allOp(float n1, float n2, float n3, float n4, float n5) {return n1 * n2 / n3 + n4 - n5;}


//Correct or Wrong Identifier
void identifier(int a, int b){
    if(a == b){ 
    printf("KORIQUE!!!");
    }
    else if(a != b){
    printf("ENGKK!!");
    counter++;
    }
}

//Prototype Function of Stages
void stage1();
void stage2();
void stage3();
void stage4();
void stage5();
void final_stage();


int main(){
    char option;
    //dashboard//
    while(option != '1' && option != '2' && option != '3'){ //ASCII CODE [1] is 49, [2] is 50, [3] is 51//
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n[2] SIGN UP\n[3] EXIT\n");
    option = getch();
    option = toupper(option);
        switch(option){
            case '1' : system("cls"); login(); break;
            case '2' : system("cls"); signup(); break;
            case '3' : system("cls");  break;
            default  : printf("\nINVALID KEY SELECTION\n"); getch(); system("cls"); continue;
        }
    }
return 0;
}
//SIGNUP FUNCTION//
void signup(){
    int tmp=0;
    char username_checker[20], password_checker[12], confirm_password[12], file_name[20], option;
    struct user account;
    FILE *f1;

    do{
        printf("SIGN UP\n\n\n");
        printf("\nEnter preferred username:\t");
        scanf("%s", username_checker);
        printf("\nEnter preferred password:\t");
        scanf("%s", confirm_password);
        printf("\nRepeat preferred password:\t");
        scanf("%s", password_checker);
        strcpy(file_name, username_checker);
        if(!strcmp(password_checker, confirm_password)){
            strcpy(account.password,password_checker);
            f1 = fopen(strcat(file_name,".dat"),"w+");
            fwrite(&account,sizeof(struct user),1,f1);
            printf("\nSIGN UP SUCCESS\nPRESS ANY KEY TO CONTINUE");
            fclose(f1);
            getch();
            tmp=1;
            system("cls");
            login();
        }
        else{
        //ascii code of [ESC] is 27
        while(option != 27){ 
            printf("\nPASSWORD DOES NOT MATCH\n\nPress any key to sign up again.\nPress ESC to go back to dashboard\n");
            option = getch();
            if(option == 27){ 
                tmp=1;
                break;
            }else{
                break;
            }
        system("cls");
        }
        }
    system("cls");
    }while(tmp!=1);
main(); 
}//END OF SIGNUP FUNCTION//

//LOGIN//
void login(){
    char username_checker[20], password_checker[12], file_name[20];
    struct user account;
    FILE *f1;
    printf("LOG IN\n\n\n");
    printf("\nEnter username:\t");
    scanf("%s", username_checker);
    printf("\nEnter password:\t");
    scanf("%s", password_checker);
    strcpy(file_name,username_checker);
    f1 = fopen(strcat(file_name,".dat"),"r");
    if(f1 == NULL){
        fclose(f1);
        printf("\nUSER DOES NOT EXIST");
        getch();
        system("cls");
        main();
    }
    else{
        while(fread(&account, sizeof(struct user),1,f1)!=EOF){
            if(!strcmp(account.password,password_checker)){
                fclose(f1);
                system("cls");
                menu();
                break;
            }
            else{
                fclose(f1);
                printf("\nINCORRECT PASSWORD");
                getch();
                system("cls");
                main();
                break;
            }
        }
    }
}//END OF LOGIN FUNCTION//

//MENU FUNCTION//
void menu(){
    int tmp=0;
    char option;

    do{
        printf("MATH WHIZ\n\n\n");
        printf("[P] START\n[L] LEADERBOARDS\n[A] ABOUT");
        printf("\n\n\nPress ESC to log out and exit\t");
        option = getch();
        option = toupper(option);
        switch(option){
            case 'P' : //ascii code of [S] is 83//
            math_whiz();
            break;

            case 'L' : //ascii code of [L] is 76//
            system("cls");
            leaderboards();
            break;
            case 'A' : //ascii code of [A] is 65//
            system("cls");
            about();
            break;

            case 27 : //ascii code of [ESC] is 27
            system("cls"); exit(0);

            default: system("cls");
        } //ascii code of [ESC] is 27
    }while(option!='S' && option!='L' && option!='P' && option!= 27); 
    
}//END OF MENU FUNCTION//

void about(){
    char option, buffer[255];
    FILE *about;
    do{
    about = fopen("about1.txt", "r");
    if(about == NULL) printf("ERROR_FILE_MISSING");
    else{
        while(fgets(buffer,255,about)!=NULL){
        printf("%s", buffer);
        }
    }
    fclose(about);
    printf("Press ESC to go back");
    option = getch();
    option = toupper(option);
    system("cls");
    }while(option!=27); //ascii code of [ESC] is 27.
    if(option == 27){
        system("cls");
        menu();
    }
}
//LEADERBOARDS// ---DISPLAY LANG MUNA GUYS, KULANG PA SA LOGIC YUNG PROGRAMMER---
void leaderboards(){
    int i;
    char option;
    do{
    printf("LEADERBOARDS\n\n\n");
    for(i = 0; i<25; i++) printf("-");
    printf("\n");
    printf("| NO. | USERNAME | STAGE |");
    printf("\n");
    for(i = 0; i<25; i++) printf("-");
    printf("\n---DISPLAY LANG MUNA GUYS, KULANG PA SA LOGIC YUNG PROGRAMMER---\n");
    printf("\nPress ESC to go back");
    option = getch();
    option = toupper(option);
    system("cls");
    }while(option!=27); //ascii code of [ESC] is 27.
    if(option==27){
        system("cls");
        menu();
    }
}//END OF LEADERBOARDS//

//MATH WHIZ//
void math_whiz(){
    struct user account;
    account.stage =0;
    printf("\nMATH WHIZ NA GUYS");

    if(account.stage == 0){
        system("cls");
        stage1();
    }
    // if(account.stage == 2){
    //     stage2();
    // }
    // if(account.stage == 3){
    //     stage3();
    // }
    // if(account.stage == 4){
    //     stage4();
    // }
    // if(account.stage == 5){
    //     stage5();
    // }
}//END OF MATH WHIZ//

/*

Stage 1
level 1 correct 
level 2 correct
level 3 correct
level 4 correct
level 5 wrong

-YOU HAVE 1 WRONG ANSWERS-

Press any key to try again.
Press B to go back to dashboard
Press ESC to log out and exit
---------------------------------

Stage 1
level 1 correct 
level 2 correct
level 3 correct
level 4 correct
level 5 correct

-YOU HAVE 0 WRONG ANSWERS-

Press any key to continue to the next stage.
Press B to go back to dashboard
Press ESC to log out and exit

*/

//UNDER CONSTRUCTION PA ITO MUNA SA NGAYON, PINAPATULOG NA NI INA
//TIME CHECK 2:33 AM, DEC 3, 2023

void stage1(){
    char option;
    int n1, n2, sys_ans, user_ans, level=1;
    srand(time(NULL));
    
    while(option != 27 && option != 'B'){
    printf("STAGE 1\n\n\n");
        do{
        if(level <= 2){
        n1 = (rand() % 25) + 1;
        n2 = (rand() % 25) + 1;
        printf("\n\nLEVEL %i\n",level);
        sys_ans = addition(n1,n2);
        printf("%i + %i = ", n1, n2);
        scanf("%i", &user_ans);
        identifier(user_ans, sys_ans);
        level++;
        }
        else if(level >= 3){
        n1 = (rand() % 25) + 1;
        n2 = (rand() % 25) + 1;
        printf("\n\nLEVEL %i\n",level);
        sys_ans = subtraction(n1,n2);
        printf("%i - %i = ", n1, n2);
        scanf("%i", &user_ans);
        identifier(user_ans, sys_ans);
        level++;
        }
        //if(level > 5) break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
    printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
    if(counter > 0){
    printf("\n\nPress any key to continue to the try again.");
    printf("\n\nPress [B] to go back to dashboard.");
    printf("\nPress ESC to log out and exit.");
    option = getch();
    option = toupper(option);
        if(option == 27){//ascii code of [ESC] is 27
        exit(0);
        }   
        else if(option == 'B'){
        option = 00; level = 1; counter = 0; system("cls");            
        menu(); break;
        }
        else{
        option = 00; level = 1; counter = 0; system("cls"); 
        continue;
        }
    }
    else{
    printf("\n\nPress any key to continue to the next stage.");
    printf("\n\nPress [B] to go back to dashboard.");
    printf("\nPress ESC to log out and exit.");
    option = getch();
    option = toupper(option);
        if(option == 27){//ascii code of [ESC] is 27
        exit(0); break;
        }
        else if(option == 'B'){
        option = 00; level = 1; counter = 0; system("cls");            
        menu(); break;
        }
        else{
        option = 00; level = 1; counter = 0;
        printf("\nSTAGE 2 na par call nalang function"); break;
        }
    }
    }
}