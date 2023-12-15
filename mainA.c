#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define MAX_LINES 100
#define ESC 27
#define ENTER 13
#define TAB 9
#define BACKSPACE 8

void clrscr(void){
    system("cls");
}

int counter=0, level=1;

char MW_OPTION, check_filename[20], lb_username[20];
const char stg_1='1', stg_2='2', stg_3='3', stg_4='4', stg_5='5', stg_godMode='6'; 

char USERNAME[50],PASSWORD[20]; 
char ACCOUNT_STAGE[1];

typedef struct {
    char line[100];
} Line;
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
void stage3();
void stage4();
void stage5();
void final_stage();

void updateStage(const char *username, const char *newStage, const char *filePath);
int compareStagesDesc(const void *a, const void *b);
void updateAndSort(const char *username, const char *newStage, const char *filePath);

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

//Function for auto ROUND OFF
float ROUND(float num) {
    return (num >= 0) ? (int)(num + 0.5) : (int)(num - 0.5);
}

// float ROUND(float num) {
//     if(num>=0) return (int)(num + 0.5); else return (int)(num - 0.5);
// }

//Function for Round OFF
float round_off(float value, int decimal_places)
{
  float rounded;
  float shift = pow(10, decimal_places);
  rounded = value * shift; rounded = ROUND(rounded); rounded = rounded / shift;
return rounded;
}

//Correct or Wrong Identifier
void identifier(int a, int b){//for int
    if(a == b){ 
    printf("CORRECT!!!"); //COLOR GREEN 
    }
    else if(a != b){
    printf("INCORRECT!!!"); //COLOR RED
    counter++;
    }
}
void fIdentifier(float a, float b, float c){// for point decimals, [FLOAT]
    if(a == b || a == c){
    printf("CORRECT!!!"); //COLOR GREEN
    }
    else if(a != b || a != c){
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
            if(!strcmp(password_checker, confirm_password)){
                fclose(fr);
                strcpy(USERNAME,username_checker);
                strcpy(PASSWORD,password_checker);
                ACCOUNT_STAGE[0] = stg_1;
                fw = fopen(file_name,"w");
                fprintf(fw, "%s %s %s\n",USERNAME,PASSWORD,ACCOUNT_STAGE); 
                fclose(fw);
                //-----------------------------------
                lb = fopen("LEADERB.txt","a");
                fprintf(lb, "%s  %s\n",USERNAME, ACCOUNT_STAGE);
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
    scanf("%s", username_checker);
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
                strcpy(lb_username,username_checker);
                printf("\nUSERNAME : %s", USERNAME); 
                printf("\nPASSWORD : %s", PASSWORD);
                printf("\nSTAGE : %s", ACCOUNT_STAGE);
                
                getch();
                fclose(fr);
                clrscr(); menu(); break;
            }
            else{
                fclose(fr);
                // printf("\nUSERNAME : %s", USERNAME);
                // printf("\nPASSWORD : %s", PASSWORD);
                // printf("\nPASSWORD : %s", ACCOUNT_STAGE);
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
        fr = fopen("LEADERB.txt", "r");
        while(fscanf(fr,"%s %s",&USERNAME,&ACCOUNT_STAGE)!=EOF){
            printf("\t\n%s\t%s", USERNAME,ACCOUNT_STAGE);
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
        while(fscanf(fr,"%s %i\n", USERNAME, ACCOUNT_STAGE)==1){
            if(ACCOUNT_STAGE[0] == stg_1){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage1(); break;
            }
            else if(ACCOUNT_STAGE[0] == stg_2){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage2(); break;
            }
            else if(ACCOUNT_STAGE[0] == stg_3){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage3(); break;
            }
            else if(ACCOUNT_STAGE[0] == stg_4){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage4(); break;
            }
            else if(ACCOUNT_STAGE[0] == stg_5){
                //printf("%i\n", loc_acc.stage); getch(); 
                clrscr(); stage5(); break;

            }
            else if(ACCOUNT_STAGE[0] == stg_godMode){ 
                clrscr(); final_stage(); break;
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
    printf("\n\nYOU HAVE %i INCORRECT ANSWERS", counter);
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
    printf("--Press any key to NEXT STAGE.");
    printf("--Press [B] to go back to MENU.");
    printf("--Press ESC to EXIT & LOG OUT.");
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
    int n1, n2, sys_ans, user_ans;
    FILE *fw;
    char ign[20];
    // int structIndex=1;
    // long offset = sizeof(ACCOUNT_STAGE) * structIndex;

    strcpy(ign,lb_username);
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
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "r+");
    if (fw == NULL) {
        printf("Error updating file.\n");
        return;
    }
    else{
        ACCOUNT_STAGE[0] = stg_2;
        fseek(fw, -3, SEEK_END);
        fprintf(fw,"%s", ACCOUNT_STAGE);
        fclose(fw);
    }
    updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,ACCOUNT_STAGE,"LEADERB.txt");
    
stage2();
}

void stage2(){ //MULTIPLICATION
    int n1, n2, sys_ans, user_ans;
    FILE *fw;
    char ign[20];

    strcpy(ign,lb_username);
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
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "r+");
    if (fw == NULL) {
        printf("Error updating file.\n");
        return;
    }
    else{
        ACCOUNT_STAGE[0] = stg_3;
        fseek(fw, -3, SEEK_END);
        fprintf(fw,"%s", ACCOUNT_STAGE);
        fclose(fw);
    }
    updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,ACCOUNT_STAGE,"LEADERB.txt");
stage3();
}

void stage3(){ //DIVISION
    float n1, n2, sys_ans1, sys_ans2, user_ans;
    FILE *fw;
    char ign[20];

    strcpy(ign,lb_username);
    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 3\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans1 = divide(n1, n2);
            sys_ans2 = divide(n1, n2);
            sys_ans1 = round_off(sys_ans1,1);
            sys_ans2 = round_off(sys_ans2,2);
            printf("bot ans 1 dplaces: %f\n", sys_ans1);
            printf("bot ans 2 dplaces: %f\n", sys_ans2);
            printf("%.f / %.f = ", n1, n2);
            scanf("%f", &user_ans);
            fIdentifier(user_ans, sys_ans1, sys_ans2);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "r+");
    if (fw == NULL) {
        printf("Error updating file.\n");
        return;
    }
    else{
        ACCOUNT_STAGE[0] = stg_4;
        fseek(fw, -3, SEEK_END);
        fprintf(fw,"%s", ACCOUNT_STAGE);
        fclose(fw);
    }
    updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,ACCOUNT_STAGE,"LEADERB.txt");
stage4();
}

void stage4(){ //MIXED OF ADDITION AND SUBTRACTION
    int n1, n2, n3, sys_ans, user_ans;
    FILE *fw;
    char ign[20];

    strcpy(ign,lb_username);
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
            printf("bot ans: %i\n", sys_ans);
            printf("%i + %i - %i = ", n1, n2, n3);
            scanf("%i", &user_ans);
            identifier(user_ans, sys_ans);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "r+");
    if (fw == NULL) {
        printf("Error updating file.\n");
        return;
    }
    else{
        ACCOUNT_STAGE[0] = stg_5;
        fseek(fw, -3, SEEK_END);
        fprintf(fw,"%s", ACCOUNT_STAGE);
        fclose(fw);
    }
    updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,ACCOUNT_STAGE,"LEADERB.txt");
stage5();
}

void stage5(){ //MIXED OF MULTIPLICATION AND DIVISION
    float n1, n2, n3, sys_ans1, sys_ans2, user_ans;
    FILE *fw;
    char ign[20];

    strcpy(ign,lb_username);
    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
        printf("STAGE 5\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            n3 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans1 = mult_div(n1, n2, n3);
            sys_ans2 = mult_div(n1, n2, n3);
            sys_ans1 = round_off(sys_ans1,1);
            sys_ans2 = round_off(sys_ans2,2);
            printf("bot ans 1 dplaces: %f\n", sys_ans1);
            printf("bot ans 2 dplaces: %f\n", sys_ans2);
            printf("%.f x  %.f / %.f = ", n1, n2, n3);
            scanf("%f", &user_ans);
            fIdentifier(user_ans, sys_ans1, sys_ans2);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    fw = fopen(check_filename, "r+");
    if (fw == NULL) {
        printf("Error updating file.\n");
        return;
    }
    else{
        ACCOUNT_STAGE[0] = stg_godMode;
        fseek(fw, -3, SEEK_END);
        fprintf(fw,"%s", ACCOUNT_STAGE);
        fclose(fw);
    }
    updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,ACCOUNT_STAGE,"LEADERB.txt");
final_stage();
}

void final_stage(){ //MIXED OF ALL OPERATORS
    float n1, n2, n3, n4, n5, sys_ans1, sys_ans2, user_ans;

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
            sys_ans1 = all_op(n1, n2, n3, n4, n5);
            sys_ans2 = all_op(n1, n2, n3, n4, n5);
            sys_ans1 = round_off(sys_ans1,1);
            sys_ans2 = round_off(sys_ans2,1);
            printf("bot ans 1 dplaces: %f\n", sys_ans1);
            printf("bot ans 2 dplaces: %f\n", sys_ans2);
            printf("%.f +  %.f - %.f x %.f / %.f = ", n1, n2, n3, n4, n5);
            scanf("%f", &user_ans);
            fIdentifier(user_ans, sys_ans1, sys_ans2);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        option_prompt();
        if(MW_OPTION == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    printf("\n\nCONGRATULATIONS!\n MATH WHIZ TEAM ARE GLAD FOR YOU TO MADE IT HERE.\n");
    printf("You are now a certified \"MATH WHIZ'er\"");
}

void updateStage(const char *username, const char *newStage, const char *filePath){
    char BUFFER[100];
    FILE *fr = fopen(filePath, "r+");
    
    if (fr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while (fgets(BUFFER, sizeof(BUFFER), fr) != NULL) {
        if (strstr(BUFFER, username) != NULL) {
            //snprintf(BUFFER, sizeof(BUFFER), "%s %s\n", username, newStage);
            sprintf(BUFFER,"%s %s\n",username, newStage);
            fseek(fr, (-strlen(BUFFER)-1), SEEK_CUR);
            fputs(BUFFER, fr);
            break;
        }
    }
    fclose(fr);
}

int compareStagesDesc(const void *a, const void *b) {
    // Comparison function for qsort based on stages in descending order
    const char *stageA = strchr(((Line *)a)->line, ' ');
    const char *stageB = strchr(((Line *)b)->line, ' ');
    
    if (stageA == NULL || stageB == NULL) {
        fprintf(stderr, "Error extracting stages for comparison.\n"); exit(EXIT_FAILURE);
    }
    return strcmp(stageB + 2, stageA + 2);
}

void updateAndSort(const char *username, const char *newStage, const char *filePath) {
    int i;
    FILE *fr = fopen(filePath, "r+");
    Line lines[MAX_LINES];
    int lineCount = 0;
    if (fr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(lines[lineCount].line, sizeof(lines[lineCount].line), fr) != NULL) {
        lineCount++;
        if (lineCount >= MAX_LINES) {
            fprintf(stderr, "Too many lines in the file. Increase MAX_LINES.\n");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < lineCount; i++) {
        if (strstr(lines[i].line, username) != NULL) {
            //snprintf(lines[i].line, sizeof(lines[i].line), "%s  %s\n", username, newStage);
            sprintf(lines[i].line,"%s  %s\n",username, newStage);
            break;
        }
    }
    qsort(lines, lineCount, sizeof(Line), compareStagesDesc);
    fseek(fr, 0, SEEK_SET);
    for (i = 0; i < lineCount; i++) {
        fputs(lines[i].line, fr);
    }
    fclose(fr);
}