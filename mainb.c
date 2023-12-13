#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define ESC 27
#define ENTER 13
#define TAB 9
#define BACKSPACE 8

void clrscr(void){
    system("cls");
}

int counter=0, level=1;
char USERNAME[50], PASSWORD[20], MW_OPTION, check_filename[20];
//const int stg_1=1, stg_2=2, stg_3=3, stg_4=4, stg_5=5, stg_godMode=6; 
const char stg_1='a', stg_2='b', stg_3='c', stg_4='d', stg_5='e', stg_godMode='f'; 
char ACCOUNT_STAGE[6];
// struct user{
//     char username[20], password[12];
//     int stage;
// }glob_acc;


//PROTOTYPE FUNCTIONS OF SYSTEM OUTLINE/GUIDELINES FLOW
void signup();
void login();
void menu();
void math_whiz();
void about();
void leaderboards();

//Prototype Function of Stages
void stage1();
void stage2();
// void stage3();
// void stage4();
// void stage5();
// void final_stage();

//MAIN OPTION PROMPT
void option_prompt();

//Function of Operators
int addition(int n1, int n2) {return n1 + n2;}
int subtract(int n1, int n2) { return n1 - n2; }
int multiply(int n1, int n2) { return n1 * n2; }
float divide(float n1, float n2) { return n1 / n2; }
//Function of Mixed Operators
int add_sub(int n1, int n2, int n3) { return n1 + n2 - n3; }
float mult_div(float n1, float n2, float n3) { return n1 * n2 / n3; }
float all_op(float n1, float n2, float n3, float n4, float n5) {return n1 * n2 / n3 + n4 - n5;}

//Correct or Wrong Identifier
void identifier(int a, int b){//for int
    if(a == b) printf("CORRECT!!!"); //COLOR GREEN 
    else if(a != b){
        printf("INCORRECT!!!"); //COLOR RED
        counter++;
    }
}
void fIdentifier(float a, float b){// for point decimals, [FLOAT]
    if(a == b) printf("CORRECT!!!"); //COLOR GREEN
    else if(a != b){
        printf("INCORRECT!!!"); //COLOR RED
        counter++;
    }
}

//HIDE THE PASSWORD INPUT
void hide_input(char password[12]){

int i=0;
char key;
while(1){
    key = getch();
    if(key == TAB|| key == ENTER ){
        password[i] = '\0';
        break;
    }
    else if(key == BACKSPACE){
        if(i>0){
            i--;
            printf("\b \b");
        }
    }
    else{
        password[i++] = key;
        printf("* \b");
    }
}
}

int main(){
    char option;
    clrscr();
    //dashboard//
    do{ //ASCII CODE [1] is 49, [2] is 50, [3] is 51//
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n[2] SIGN UP\n");
    printf("\n\n\nPRESS ESC TO EXIT\n");
    option = getch();
        switch(option){
            case '1' : login(); break;
            case '2' : signup(); break;
            case ESC : clrscr();  break;
            default  : printf("\nINVALID KEY SELECTION\n"); getch();
            clrscr(); break;
        }
    }while(option != '1' && option != '2' && option != ESC);
return 0;
}
//SIGNUP FUNCTION//
 //GLOBAL VARIABLE DECLARATION FOR CONTROL OF STAGES RE-DIRECTION
void signup(){
    // int tmp=0;
    char username_checker[50], password_checker[20], confirm_password[20], file_name[50], option;
    FILE *fw, *fr, *lb;
    clrscr();

    do{
        printf("SIGN UP\n\n\n");
        printf("\nEnter preferred username:\t");
        scanf("%s", &username_checker);
        printf("\nEnter preferred password:\t");
        hide_input(password_checker);
        //scanf("%s", &password_checker);
        printf("\nRepeat preferred password:\t");
        hide_input(confirm_password);
        //scanf("%s", &confirm_password);
        strcpy(file_name, username_checker);
        fr = fopen(strcat(file_name,".dat"),"r");
        //printf("\n%s",check_filename);getch();
        if(fr == NULL){
            fclose(fr);
            if(!strcmp(password_checker, confirm_password)){
                strcpy(USERNAME,username_checker);
                strcpy(PASSWORD,password_checker);
                ACCOUNT_STAGE[0] = stg_1;
                fw = fopen(file_name,"w");
                fprintf(fw, "%s %s %s\n",USERNAME, PASSWORD, ACCOUNT_STAGE); 
                fclose(fw);
                //-----------------------------------
                lb = fopen("lb.txt","a");
                fprintf(fw, "%s %s\n",USERNAME, ACCOUNT_STAGE);
                fclose(lb);
                printf("\nSIGN UP SUCCESS\nPRESS ANY KEY TO CONTINUE");
                option = 00; getch(); clrscr(); login();
            }
            else{//ascii code of [ESC] is 27
                while(option!=ESC){ 
                    printf("\nPASSWORD DOES NOT MATCH\n\nPress any key to sign up again.\nPress ESC to go back to dashboard\n");
                    option = getch();
                    if(option == ESC) option = 00; 
                    break;
                }
            }
        }
        else{
            option = 00;
            printf("\nUSERNAME ALREADY EXIST"); getch();
            fclose(fr); 
        }clrscr();
    }while(option!=00);
    main(); 
}//END OF SIGNUP FUNCTION//

//LOGIN//
void login(){
    char username_checker[50], password_checker[20];
    FILE *fr;
    clrscr();

    printf("LOG IN\n\n\n");
    printf("\nEnter username:\t");
    scanf("%s", &username_checker);
    printf("\nEnter password:\t");
    hide_input(password_checker);
    //scanf("%s", &password_checker);
    strcpy(check_filename,username_checker); //check_filename ay global variable
    //printf("%s", check_filename); getch(); this line was only for checking the string value of username
    fr = fopen(strcat(check_filename,".dat"),"r");
    if(fr == NULL){
        fclose(fr);
        printf("\nUSER DOES NOT EXIST"); getch();
        clrscr();
        main();
    }
    else{
        //(fscanf(f1,"%s", account.password)!=EOF){
        while(fscanf(fr, "%s %s %s\n", USERNAME, PASSWORD, ACCOUNT_STAGE)!=EOF){ //READ BINARY FROM FILE
            if(!strcmp(PASSWORD,password_checker)){
                printf("\nUSERNAME : %s", USERNAME);
                printf("\nPASSWORD : %s", PASSWORD);
                printf("\nSTAGE : %s", ACCOUNT_STAGE);
                
                getch();
                fclose(fr);
                clrscr(); menu(); break;
            }
            else{
                fclose(fr);
                printf("\nUSERNAME : %s", USERNAME);
                printf("\nPASSWORD : %s", PASSWORD);
                printf("\nPASSWORD : %s", ACCOUNT_STAGE);
                // printf("\nINCORRECT PASSWORD");getch();
                clrscr(); main(); break;
            }
        }
    }
}//END OF LOGIN FUNCTION//

//MENU FUNCTION//
void menu(){
    char option;

    while(option!='P' && option!='L' && option!='A' && option!= ESC){
        printf("MATH WHIZ\n\n\n");
        printf("[P] START\n[L] LEADERBOARDS\n[A] ABOUT");
        printf("\n\n\nPress ESC to EXIT & LOG OUT\t");
        option = getch();
        option = toupper(option);
        switch(option){
            case 'P' : //ascii code of [P] is 80//
            math_whiz();
            break;

            case 'L' : //ascii code of [L] is 76//
            clrscr();
            leaderboards();
            break;
            case 'A' : //ascii code of [A] is 65//
            clrscr();
            about();
            break;

            case ESC : //ascii code of [ESC] is 27//
            clrscr(); exit(0);

            default: clrscr();
        }
    }
    
}//END OF MENU FUNCTION//

void about(){
    char option, BUFFER_FCONTENT[256];
    FILE *fr;

    int MAX_BUFFER_LINE = sizeof(BUFFER_FCONTENT);
    //printf("SIZE %d", MAX_BUFFER_LINE); getch(); THIS LINE AY ONLY FOR CHECKING OF BUFFER VALUE IN BYTES 
    do{
        fr = fopen("about1.txt", "r");
        if(fr == NULL) printf("ERROR_FILE_MISSING");
        else{
            while(fgets(BUFFER_FCONTENT,MAX_BUFFER_LINE,fr)!=NULL)
            printf("%s", BUFFER_FCONTENT);
        }
        fclose(fr);
        printf("Press ESC to go back");
        option = getch();
        option = toupper(option);
        clrscr();
    }while(option!=ESC); //ascii code of [ESC] is 27.
    clrscr();
    menu();
}
//LEADERBOARDS// ---DISPLAY LANG MUNA GUYS, KULANG PA SA LOGIC YUNG PROGRAMMER---
void leaderboards(){
    int i;
    char option;
    FILE *fr;
    do{
        printf("LEADERBOARDS\n\n\n");
        for(i = 0; i<25; i++) printf("-");
        printf("\n");
        printf("| NO. | USERNAME | STAGE |");
        printf("\n");
        for(i = 0; i<25; i++) printf("-");
        fr = fopen("lb.txt", "r");
        while(fscanf(fr,"%s %s",USERNAME,ACCOUNT_STAGE)!=EOF){
            printf("\n\t%7s", USERNAME);
            printf("\t%s", ACCOUNT_STAGE);
            // printf("\t%7s", ACCOUNT_STAGE);
        }
        // while(fread(&glob_acc, sizeof(struct user),1,fr)){
        //     printf("\n\t%s", glob_acc.username);
        //     printf("\t%7i", glob_acc.stage);
        // }
        fclose(fr);
        printf("\nPress ESC to go back");
        option = getch();
        option = toupper(option);
        clrscr();
    }while(option!=ESC); //ascii code of [ESC] is 27.
    clrscr();
    menu();
}//END OF LEADERBOARDS//

//MATH WHIZ//
void math_whiz(){
    FILE *fr;

    fr = fopen(check_filename,"r");
    if(fr == NULL){
        printf("ERROR OPENING FILE");
        fclose(fr); exit(0);
    }
    else{
        //while(fread(&loc_acc, sizeof(struct user),1,fr)){
        while(fscanf(fr,"%s %s\n", &USERNAME, &ACCOUNT_STAGE)==1){
            if(ACCOUNT_STAGE[0] == stg_1){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage1(); break;
            }
            else if(ACCOUNT_STAGE[1] == stg_2){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage2(); break;
            }
            else if(ACCOUNT_STAGE[2] == stg_3){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); //stage3(); break;
            }
            else if(ACCOUNT_STAGE[3] == stg_4){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); //stage4(); break;
            }
            else if(ACCOUNT_STAGE[4] == stg_5){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); // stage5(); break;

            }
            else if(ACCOUNT_STAGE[5] == stg_godMode){ 
                clrscr(); //final_stage(); break;
            }
            else{
                printf("%s", ACCOUNT_STAGE);
                printf("ERROR ON ALLOCATING OF LOADED PROGRESS"); 
                getch(); exit(0); 
            }
        }
    }
    fclose(fr); 
}//END OF MATH WHIZ//

void option_prompt(){
    if(counter > 0){
    printf("\n\n--Press any key to TRY AGAIN.");
    printf("\n--Press [B] to go back to MENU.");
    printf("\n--Press ESC to EXIT & LOG OUT.");
    MW_OPTION = getch();
    MW_OPTION = toupper(MW_OPTION);
        switch (MW_OPTION){
            case 'B' : //Press B to go back to menu
            MW_OPTION = 01; level = 1; counter = 0;
            clrscr(); menu(); break;

            case ESC : // Press ESC to EXIT & LOG OUT
            exit(0);
                    
            default: //Press any key to TRY AGAIN
            MW_OPTION = 01; level = 1; counter = 0;
            clrscr(); 
        }
    }
    else{
    printf("\n\n--Press any key to NEXT STAGE.");
    printf("\n--Press [B] to go back to MENU.");
    printf("\n--Press ESC to EXIT & LOG OUT.");
    MW_OPTION = getch();
    MW_OPTION = toupper(MW_OPTION);
        switch(MW_OPTION){ 
            case 'B' : //Press [B] to go back to MENU
            MW_OPTION = 00; level = 1; counter = 0;  
            clrscr(); menu(); break;

            case ESC : //Press ESC to EXIT & LOG OUT
            exit(0);

            default: //Press any key to NEXT STAGE
            MW_OPTION = 00; level = 1; counter = 0;
            clrscr(); break;
        }
    }
}

void stage1(){ //ADDITION & SUBTRACTION
    int n1, n2, sys_ans, user_ans,found=0;
    FILE *fw,*lb;
    char ign[20];
    int structIndex=1;
    long offset = sizeof(ACCOUNT_STAGE) * structIndex;

    //strcpy(ign,USERNAME);
    //strcpy(loc_acc.username,ign);
    
    srand(time(NULL));
    //printf("\n%s", check_filename); .dat
    //printf("\n%s", loc_acc.username);
    //printf("\n%s", ign);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 1\n");
        do{
            n1 = (rand() % 25) + 1;
            n2 = (rand() % 25) + 1;
            if(level <= 2){
            printf("\n\nLEVEL %i\n",level);
            sys_ans = addition(n1,n2);
            printf("%i + %i = ", n1, n2);
            scanf("%i", &user_ans);
            identifier(user_ans, sys_ans);
            level++;
            }
            else if(level >= 3){
            printf("\n\nLEVEL %i\n",level);
            sys_ans = subtract(n1,n2);
            printf("%i - %i = ", n1, n2);
            scanf("%i", &user_ans);
            identifier(user_ans, sys_ans);
            level++;
            }
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "rb+");
    if (fw == NULL) {
        printf("Error opening file for update.\n");
        return;
    }

    // Move the file pointer to the position where you want to update the struct
    fseek(fw, offset, SEEK_SET);

    // Update the stage information
    ACCOUNT_STAGE[1] = stg_2;

    // Write the updated struct back to the file
    fprintf(fw,"%i", ACCOUNT_STAGE);

    // Close the file
    fclose(fw);
    // fw = fopen(check_filename, "w");
    // if(fw == NULL){ 
    //     printf("ERROR_FETCHING_FILES");
    // }
    // else{
    //     glob_acc.stage = stg_2;
    //     //fseek(fw,offset, SEEK_SET);
    //     fwrite(&glob_acc, sizeof(struct user),1,fw);
    //     fclose(fw);
    // }

    // lb = fopen("leaderboards.txt", "r");
    // while(fread(&glob_acc,sizeof(struct user),1,lb)){
    //     if(!strcmp(glob_acc.username,ign)){ 
    //     found=1;
    //     }
    // }
    // fclose(lb);

    // if(found){
    //     fw = fopen(check_filename,"r");
    //     lb = fopen("leaderboards.txt","w");
    //     fseek(fw,offset, SEEK_SET);
    //     while(fread(&glob_acc,sizeof(struct user),1,fw)){
    //         fseek(lb,offset, SEEK_SET);
    //         fwrite(&glob_acc,sizeof(struct user),1,lb);
    //     }
    //     fclose(fw);
    //     fclose(lb);
    // }
    // else{
    //     printf("\nUSER NOT FOUND");
    //     fclose(fw);
    //     fclose(lb);
    // }
stage2();
}

void stage2(){ //MULTIPLICATION
    int n1, n2, sys_ans, user_ans;
    FILE *fw;

    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 2\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = multiply(n1,n2);
            printf("%i x %i = ", n1, n2);
            scanf("%i", &user_ans);
            identifier(user_ans, sys_ans);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "w");
    if(fw == NULL){ 
        printf("ERROR_FETCHING_FILES");
    }
    else{
        ACCOUNT_STAGE[2] = stg_3;
        fprintf(fw, "\n%i", ACCOUNT_STAGE);
        //fwrite(&glob_acc, sizeof(struct user),1,fw);
        fclose(fw);
    }
}

// void stage3(){ //DIVISION
//     float n1, n2, sys_ans, user_ans;
//     FILE *fw;

//     srand(time(NULL));
//     //printf("%s", check_filename);
//     while(MW_OPTION != ESC && MW_OPTION != 'B'){
//         printf("STAGE 3\n");
//         do{
//             n1 = (rand() % 10) + 1;
//             n2 = (rand() % 10) + 1;
//             printf("\n\nLEVEL %i\n",level);
//             sys_ans = divide(n1,n2);
//             round(sys_ans);
//             printf("bot ans: %f\n", sys_ans);
//             printf("%.f / %.f = ", n1, n2);
//             scanf("%f", &user_ans);
//             fIdentifier(user_ans, sys_ans);
//             level++;
//             //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
//         }while(level<=5);
//         printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
//         option_prompt();
//         if(MW_OPTION == 00) break; 
//         //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
//     }
//     fw = fopen(check_filename, "w");    
//     if(fw == NULL){ 
//         printf("ERROR_FETCHING_FILES");
//         fclose(fw);
//         exit(0);
//     }
//     else{
//         glob_acc.stage = stg_4;
//         //fprintf(f1, "\n%i", account.stage);
//         fwrite(&glob_acc, sizeof(struct user),1,fw);
//         fclose(fw);
//     }
//     stage4();
// }

// void stage4(){ //MIXED OF ADDITION AND SUBTRACTION
//     int n1, n2, n3, sys_ans, user_ans;
//     FILE *fw;

//     srand(time(NULL));
//     //printf("%s", check_filename);
//     while(MW_OPTION != ESC && MW_OPTION != 'B'){
//         printf("STAGE 4\n");
//         do{
//             n1 = (rand() % 10) + 1;
//             n2 = (rand() % 10) + 1;
//             n3 = (rand() % 10) + 1;
//             printf("\n\nLEVEL %i\n",level);
//             sys_ans = add_sub(n1, n2, n3);
//             printf("bot ans: %f\n", sys_ans);
//             printf("%i + %i - %i = ", n1, n2, n3);
//             scanf("%i", &user_ans);
//             identifier(user_ans, sys_ans);
//             level++;
//             //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
//         }while(level<=5);
//         printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
//         option_prompt();
//         if(MW_OPTION == 00) break; 
//         //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
//     }
//     fw = fopen(check_filename, "w");    
//     if(fw == NULL){ 
//         printf("ERROR_FETCHING_FILES");
//         fclose(fw);
//         exit(0);
//     }
//     else{
//         glob_acc.stage = stg_5;
//         //fprintf(f1, "\n%i", account.stage);
//         fwrite(&glob_acc, sizeof(struct user),1,fw);
//         fclose(fw);
//     }
//     stage5();
// }

// void stage5(){ //MIXED OF MULTIPLICATION AND DIVISION
//     float n1, n2, n3, sys_ans, user_ans;
//     FILE *fw;

//     srand(time(NULL));
//     //printf("%s", check_filename);
//     while(MW_OPTION != ESC && MW_OPTION != 'B'){
//         printf("STAGE 5\n");
//         do{
//             n1 = (rand() % 10) + 1;
//             n2 = (rand() % 10) + 1;
//             n3 = (rand() % 10) + 1;
//             printf("\n\nLEVEL %i\n",level);
//             sys_ans = mult_div(n1, n2, n3);
//             printf("bot ans: %f\n", sys_ans);
//             printf("%.f x  %.f / %.f = ", n1, n2, n3);
//             scanf("%f", &user_ans);
//             fIdentifier(user_ans, sys_ans);
//             level++;
//             //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
//         }while(level<=5);
//         printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
//         option_prompt();
//         if(MW_OPTION == 00) break; 
//         //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
//     }
//     fw = fopen(check_filename, "w");    
//     if(fw == NULL){ 
//         printf("ERROR_FETCHING_FILES");
//         fclose(fw);
//         exit(0);
//     }
//     else{
//         glob_acc.stage = stg_godMode;
//         //fprintf(f1, "\n%i", account.stage);
//         fwrite(&glob_acc, sizeof(struct user),1,fw);
//         fclose(fw);
//     }
//     final_stage();
// }

// void final_stage(){ //MIXED OF ALL OPERATORS
//     float n1, n2, n3, n4, n5, sys_ans, user_ans;

//     srand(time(NULL));
//     //printf("%s", check_filename);
//     while(MW_OPTION != ESC && MW_OPTION != 'B'){
//         printf("FINAL STAGE\n");
//         do{
//             n1 = (rand() % 10) + 1;
//             n2 = (rand() % 10) + 1;
//             n3 = (rand() % 10) + 1;
//             n4 = (rand() % 10) + 1;
//             n5 = (rand() % 10) + 1;
//             printf("\n\nLEVEL %i\n",level);
//             sys_ans = all_op(n1, n2, n3, n4, n5);
//             printf("bot ans: %f\n", sys_ans);
//             printf("%.f +  %.f - %.f x %.f / %.f = ", n1, n2, n3, n4, n5);
//             scanf("%f", &user_ans);
//             fIdentifier(user_ans, sys_ans);
//             level++;
//             //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
//         }while(level<=5);
//         printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
//         option_prompt();
//         if(MW_OPTION == 00) break; 
//         //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
//     }
//     printf("\n\nCONGRATULATIONS!\n MATH WHIZ TEAM ARE GLAD FOR YOU TO MADE IT HERE.\n");
//     printf("You are now a certified \"MATH WHIZ\"");
// }
