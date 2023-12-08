#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

int counter=0, level=1;
char main_option, check_filename[20];

enum stages{
    stage_1 = 1,
    stage_2 = 2,
    stage_3 = 3,
    stage_4 = 4,
    stage_5 = 5,
    stage_god = 6
};
struct user{
    char username[20], password[12];
    int stage;
};

struct user acc1;
//PROTOTYPE FUNCTIONS OF SYSTEM OUTLINE/GUIDELINES FLOW
void signup();
void login();
void menu();
void math_whiz();
void about();
void leaderboards();

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
void identifier(int a, int b){
    if(a == b) printf("KORIQUE!!!");
    else if(a != b){
        printf("ENGKK!!");
        counter++;
    }
}

void identifier1(float a, float b){
    if(a == b) printf("KORIQUE!!!");
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

//MAIN OPTION PROMPT
void option_prompt();

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
 //GLOBAL VARIABLE DECLARATION FOR CONTROL OF STAGES RE-DIRECTION
void signup(){
    // int tmp=0;
    char username_checker[20], password_checker[12], confirm_password[12], file_name[20], option;
    struct user acc;
    FILE *f1;

    do{
        printf("SIGN UP\n\n\n");
        printf("\nEnter preferred username:\t");
        scanf("%s", &username_checker);
        printf("\nEnter preferred password:\t");
        scanf("%s", &confirm_password);
        printf("\nRepeat preferred password:\t");
        scanf("%s", &password_checker);
        strcpy(file_name, username_checker);
        if(!strcmp(password_checker, confirm_password)){
            strcpy(acc.password,confirm_password);
            //strcpy(acc.username,file_name);
            acc.stage = stage_1;
            f1 = fopen(strcat(file_name,".dat"),"w");
            //fprintf(f1,"%s\t%i\n",acc.password); //WRITE TO NG STRING SA FILE HEHE 
            fwrite(&acc,sizeof(struct user),1,f1);    // PANG WRITE  LANG NG BINARY CANCEL MUNA  
            printf("\nSIGN UP SUCCESS\nPRESS ANY KEY TO CONTINUE");
            fclose(f1);
            f1 = fopen("leaderboards.txt","a");
            fprintf(f1, "%s\t%i\n",acc.username,acc.stage);
            fclose(f1);
            getch();
            option = 01;
            system("cls");
            login();
            }
        else{//ascii code of [ESC] is 27
            while(option != 27){ 
                printf("\nPASSWORD DOES NOT MATCH\n\nPress any key to sign up again.\nPress ESC to go back to dashboard\n");
                option = getch();
                if(option == 27){ 
                    option = 01;
                    break;
                }
                break;
            }
        }
        system("cls");
    }while(option!=01);
main(); 
}//END OF SIGNUP FUNCTION//

//LOGIN//
void login(){
    char username_checker[20], password_checker[12];
    FILE *f1;

    printf("LOG IN\n\n\n");
    printf("\nEnter username:\t");
    scanf("%s", &username_checker);
    printf("\nEnter password:\t");
    scanf("%s", &password_checker);
    strcpy(check_filename,username_checker);
    //printf("%s", check_filename); getch();
    f1 = fopen(strcat(check_filename,".dat"),"r");
    if(f1 == NULL){
        fclose(f1);
        printf("\nUSER DOES NOT EXIST");
        getch();
        system("cls");
        main();
    }
    else{
        //(fscanf(f1,"%s", account.password)!=EOF){
        while(fread(&acc1, sizeof(struct user),1,f1)!=EOF){ //READ BINARY FROM FILE
            if(!strcmp(acc1.password,password_checker)){
            fclose(f1);
            system("cls"); menu(); break;
            }
            else{
            fclose(f1);
            printf("\nINCORRECT PASSWORD");getch();
            system("cls"); main(); break;
            }
        }
    }
}//END OF LOGIN FUNCTION//

//MENU FUNCTION//
void menu(){
    char option;

    while(option!='P' && option!='L' && option!='A' && option!= 27){
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
            system("cls");
            leaderboards();
            break;
            case 'A' : //ascii code of [A] is 65//
            system("cls");
            about();
            break;

            case 27 : //ascii code of [ESC] is 27//
            system("cls"); exit(0);

            default: system("cls");
        }
    }
    
}//END OF MENU FUNCTION//

void about(){
    char option, buffer[255];
    FILE *fabt;
    do{
        fabt = fopen("about1.txt", "r");
        if(fabt == NULL) printf("ERROR_FILE_MISSING");
        else{
            while(fgets(buffer,255,fabt)!=NULL)
            printf("%s", buffer);
        }
        fclose(fabt);
        printf("Press ESC to go back");
        option = getch();
        option = toupper(option);
        system("cls");
    }while(option!=27); //ascii code of [ESC] is 27.
    system("cls");
    menu();
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
    system("cls");
    menu();
}//END OF LEADERBOARDS//

//MATH WHIZ//
void math_whiz(){
    //int stage_1=1, stage_2=2, stage_3=3, stage_4=4;
    char ign[20];
    struct user account;
    FILE *f1;
     
    //printf("%i\n", account.stage); getch(); //wag pansinin wala to. 
    //strcpy(ign,check_filename);
    f1 = fopen(check_filename,"r");
    if(f1 == NULL){
        printf("ERROR OPENING FILE");
        fclose(f1); exit(0);
    }
    else{
        while(fread(&account, sizeof(struct user),1,f1)!=EOF){
        //while(fscanf(f1,"%i",acc.stage)!=EOF){
            if(account.stage == stage_1){
                printf("%i\n", account.stage); getch(); 
                system("cls"); stage1(); break;
            }
            else if(account.stage == stage_2){
                system("cls");
                printf("%i\n", account.stage); stage2(); break;
            //fclose(f1); system("cls"); stage2();
            }
            else if(account.stage == stage_3){
                system("cls");
                printf("%i\n", account.stage); stage3(); break;
            //fclose(f1); system("cls"); stage2();
            }
            else if(account.stage == stage_4){
                system("cls");
                printf("%i\n", account.stage); stage4(); break;
            //fclose(f1); system("cls"); stage2();
            }
            else if(account.stage == stage_5){
                system("cls");
                printf("%i\n", account.stage); stage3(); break;
            //fclose(f1); system("cls"); stage2();
            }
            else if(account.stage == stage_god){
                system("cls");
                printf("%i\n", account.stage); stage3(); break;
            //fclose(f1); system("cls"); stage2();
            }
            else{
                printf("ERROR"); getch(); exit(0); 
            }
        }
    }
    fclose(f1); 

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

void option_prompt(){
    if(counter > 0){
    printf("\n\n--Press any key to TRY AGAIN.");
    printf("\n--Press [B] to go back to MENU.");
    printf("\n--Press ESC to EXIT & LOG OUT.");
    main_option = getch();
    main_option = toupper(main_option);
        switch (main_option){
            
            case 'B' : //Press B to go back to menu
            main_option = 01; level = 1; counter = 0;
            system("cls"); menu(); break;

            case 27 : // Press ESC to EXIT & LOG OUT
            exit(0);
                    
            default: //Press any key to TRY AGAIN
            main_option = 01; level = 1; counter = 0;
            system("cls"); 
        }
    }
    else{
    printf("\n\n--Press any key to NEXT STAGE.");
    printf("\n--Press [B] to go back to MENU.");
    printf("\n--Press ESC to EXIT & LOG OUT.");
    main_option = getch();
    main_option = toupper(main_option);
        switch(main_option){
            
            case 'B' : //Press [B] to go back to MENU
            main_option = 00; level = 1; counter = 0;  
            system("cls"); menu(); break;

            case 27 : //Press ESC to EXIT & LOG OUT
            exit(0);

            default: //Press any key to NEXT STAGE
            main_option = 00; level = 1; counter = 0;
            system("cls"); break;
        }
    }
}

void stage1(){ //ADDITION & SUBTRACTION
    int n1, n2, sys_ans, user_ans;
    struct user account;
    FILE *f1;
    srand(time(NULL));
    printf("%s", check_filename);
    while(main_option != 27 && main_option != 'B'){
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
        if(main_option == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    f1 = fopen(check_filename, "w");
    if(f1 == NULL){ 
        printf("ERROR_FETCHING_FILES");
    }
    else{
        acc1.stage = stage_2;
        printf("\n%i", account.stage);
        getch();
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&acc1, sizeof(struct user),1,f1);
        fclose(f1);
        }
    stage2();
    }

void stage2(){ //MULTIPLICATION
    int n1, n2, sys_ans, user_ans;
    struct user account;
    FILE *f1;
    srand(time(NULL));
    printf("%s", check_filename);
    while(main_option != 27 && main_option != 'B'){
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
        if(main_option == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    f1 = fopen(check_filename, "w");
    if(f1 == NULL){ 
        printf("ERROR_FETCHING_FILES");
    }
    else{
        acc1.stage = stage_3;
        printf("\n%i", account.stage);
        getch();
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&acc1, sizeof(struct user),1,f1);
        fclose(f1);
        }
    stage3();
}

void stage3(){ //DIVISION
    int n1, n2; 
    float sys_ans, user_ans;
    struct user account;
    FILE *f1;
    srand(time(NULL));
    printf("%s", check_filename);
    while(main_option != 27 && main_option != 'B'){
        printf("STAGE 3\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = divide(n1,n2);
            printf("bot ans: %f\n", sys_ans);
            printf("%.f / %.f = ", n1, n2);
            scanf("%f", &user_ans);
            identifier1(user_ans, sys_ans);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
        option_prompt();
        if(main_option == 00) break; 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    }
    f1 = fopen(check_filename, "w");    
    if(f1 == NULL){ 
        printf("ERROR_FETCHING_FILES");
    }
    else{
        acc1.stage = stage_4;
        printf("\n%i", account.stage);
        getch();
        //fprintf(f1, "\n%i", account.stage);
        fwrite(&acc1, sizeof(struct user),1,f1);
        fclose(f1);
        }
    stage4();
}

void stage4(){
    printf("stage4 na"); getch();
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