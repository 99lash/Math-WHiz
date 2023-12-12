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
char MW_OPTION, check_filename[20];
const int stg_1=1, stg_2=2, stg_3=3, stg_4=4, stg_5=5, stg_godMode=6; 

struct user{
    char username[20], password[12];
    int stage;
}glob_acc;

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
void stage3();
void stage4();
void stage5();
void final_stage();

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
    while(option != '1' && option != '2' && option != ESC){ //ASCII CODE [1] is 49, [2] is 50, [3] is 51//
    printf("MATH WHIZ\n\n\n");
    printf("[1] LOG IN\n[2] SIGN UP\n");
    printf("\n\n\nPRESS ESC TO EXIT\n");
    option = getch();
        switch(option){
            case '1' : clrscr(); login(); break;
            case '2' : clrscr(); signup(); break;
            case ESC : clrscr();  break;
            default  : printf("\nINVALID KEY SELECTION\n"); getch();
            clrscr(); break;
        }
    }
return 0;
}
//SIGNUP FUNCTION//
 //GLOBAL VARIABLE DECLARATION FOR CONTROL OF STAGES RE-DIRECTION
void signup(){
    // int tmp=0;
    clrscr();
    char username_checker[20], password_checker[12], confirm_password[12], file_name[20], option;
    struct user loc_acc;
    FILE *fw, *fr, *lb;

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
                strcpy(loc_acc.password,confirm_password);
                //strcpy(loc_acc.username,username_checker);
                loc_acc.stage = stg_1;
                //printf("\n%s", file_name); getch();
                fw = fopen(file_name,"w");
                fwrite(&loc_acc,sizeof(struct user),1,fw);
                fclose(fw);
                //---------------------------------
                lb = fopen("leaderboards.txt","a");
                strcpy(glob_acc.username,username_checker);
                glob_acc.stage = stg_1;
                fwrite(&glob_acc,sizeof(struct user),1,lb);
                fclose(lb);
                fflush(stdin);
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
        }
    }while(option!=00);
    main(); 
}//END OF SIGNUP FUNCTION//

//LOGIN//
void login(){
    char username_checker[20], password_checker[12];
    FILE *fr;

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
        while(fread(&glob_acc, sizeof(struct user),1,fr)!=EOF){ //READ BINARY FROM FILE
            if(!strcmp(glob_acc.password,password_checker)){
            strcpy(glob_acc.password,password_checker);
            fclose(fr);
            clrscr(); menu(); break;
            }
            else{
            fclose(fr);
            printf("\nINCORRECT PASSWORD");getch();
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
    char option,buffer[255];
    struct user loc_acc;
    FILE *fr;
    do{
        printf("LEADERBOARDS\n\n\n");
        for(i = 0; i<25; i++) printf("-");
        printf("\n");
        printf("| NO. | USERNAME | STAGE |");
        printf("\n");
        for(i = 0; i<25; i++) printf("-");
        fr = fopen("leaderboards.txt", "r");
        while(fread(&loc_acc, sizeof(struct user),1,fr)){
            printf("\n\t%s", loc_acc.username);
            printf("\t%7i", loc_acc.stage);
        }
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
    struct user loc_acc;
    FILE *fr;

    fr = fopen(check_filename,"r");
    if(fr == NULL){
        printf("ERROR OPENING FILE");
        fclose(fr); exit(0);
    }
    else{
        while(fread(&loc_acc, sizeof(struct user),1,fr)){
        //while(fscanf(f1,"%i",acc.stage)!=EOF){
            if(loc_acc.stage == stg_1){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage1(); break;
            }
            else if(loc_acc.stage == stg_2){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage2(); break;
            }
            else if(loc_acc.stage == stg_3){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage3(); break;
            }
            else if(loc_acc.stage == stg_4){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage4(); break;
            }
            else if(loc_acc.stage == stg_5){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage5(); break;

            }
            else if(loc_acc.stage == stg_godMode){ 
                clrscr(); final_stage(); break;
            }
            else{
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
    struct user loc_acc;
    FILE *fw,*lb;
    char ign[20];

    strcpy(ign,glob_acc.username);
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
    fw = fopen(check_filename, "w");
    if(fw == NULL){ 
        printf("ERROR_FETCHING_FILES");
    }
    else{
        glob_acc.stage = stg_2;
        fwrite(&glob_acc, sizeof(struct user),1,fw);
        fclose(fw);
    }
    lb = fopen("leaderboards.txt", "r");
    while(fread(&glob_acc,sizeof(struct user),1,lb)){
        if(!strcmp(glob_acc.username,ign)){ 
        found=1;
        }
    }
    fclose(lb);

    if(found==1){
        fw = fopen(check_filename,"r");
        lb = fopen("leaderboards.txt","a");
        while(fread(&glob_acc,sizeof(struct user),1,fw)){
            fwrite(&glob_acc,sizeof(struct user),1,lb);
        }
        fclose(fw);
        fclose(lb);
    }
    else {
        printf("\nUSER NOT FOUND");
        fclose(fw);
        fclose(lb);
    }
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
        glob_acc.stage = stg_3;
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&glob_acc, sizeof(struct user),1,fw);
        fclose(fw);
    }
    stage3();
}

void stage3(){ //DIVISION
    float n1, n2, sys_ans, user_ans;
    FILE *fw;

    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 3\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = divide(n1,n2);
            round(sys_ans);
            printf("bot ans: %f\n", sys_ans);
            printf("%.f / %.f = ", n1, n2);
            scanf("%f", &user_ans);
            fIdentifier(user_ans, sys_ans);
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
        fclose(fw);
        exit(0);
    }
    else{
        glob_acc.stage = stg_4;
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&glob_acc, sizeof(struct user),1,fw);
        fclose(fw);
    }
    stage4();
}

void stage4(){ //MIXED OF ADDITION AND SUBTRACTION
    int n1, n2, n3, sys_ans, user_ans;
    FILE *fw;

    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 4\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            n3 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = add_sub(n1, n2, n3);
            printf("bot ans: %f\n", sys_ans);
            printf("%i + %i - %i = ", n1, n2, n3);
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
        fclose(fw);
        exit(0);
    }
    else{
        glob_acc.stage = stg_5;
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&glob_acc, sizeof(struct user),1,fw);
        fclose(fw);
    }
    stage5();
}

void stage5(){ //MIXED OF MULTIPLICATION AND DIVISION
    float n1, n2, n3, sys_ans, user_ans;
    FILE *fw;

    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 5\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            n3 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = mult_div(n1, n2, n3);
            printf("bot ans: %f\n", sys_ans);
            printf("%.f x  %.f / %.f = ", n1, n2, n3);
            scanf("%f", &user_ans);
            fIdentifier(user_ans, sys_ans);
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
        fclose(fw);
        exit(0);
    }
    else{
        glob_acc.stage = stg_godMode;
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&glob_acc, sizeof(struct user),1,fw);
        fclose(fw);
    }
    final_stage();
}

void final_stage(){ //MIXED OF ALL OPERATORS
    float n1, n2, n3, n4, n5, sys_ans, user_ans;

    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("FINAL STAGE\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            n3 = (rand() % 10) + 1;
            n4 = (rand() % 10) + 1;
            n5 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = all_op(n1, n2, n3, n4, n5);
            printf("bot ans: %f\n", sys_ans);
            printf("%.f +  %.f - %.f x %.f / %.f = ", n1, n2, n3, n4, n5);
            scanf("%f", &user_ans);
            fIdentifier(user_ans, sys_ans);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    printf("\n\nCONGRATULATIONS!\n MATH WHIZ TEAM ARE GLAD FOR YOU TO MADE IT HERE.\n");
    printf("You are now a certified \"MATH WHIZ\"");
}
/*Stage 1
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