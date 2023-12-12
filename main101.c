#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

int counter=0, level=1;
char main_option, check_filename[20];

const int stg1=1,stg2=2,stg3=3,stg4=4,stg5=5;

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
int subtract(int n1, int n2) { return n1 - n2; }
int multiply(int n1, int n2) { return n1 * n2; }
float divide(float n1, float n2) { return n1 / n2; }
//Function of Mixed Operators
int add_sub(int n1, int n2, int n3) { return n1 + n2 - n3; }
float mult_div(float n1, float n2, float n3) { return n1 * n2 / n3; }
float all_op(float n1, float n2, float n3, float n4, float n5) {return n1 * n2 / n3 + n4 - n5;}


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
            default  : printf("\nINVALID KEY SELECTION\n"); getch(); system("cls"); 
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
    FILE *f1, *lb;

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
            acc.stage = stg1;
            //strcpy(acc.username,file_name);
            //acc.stage[12] = stg2;
            f1 = fopen(strcat(file_name,".dat"),"w");
            fprintf(f1,"%s\n%i\n", acc.password, &acc.stage); //WRITE TO NG STRING SA FILE HEHE 
            //fwrite(&acc,sizeof(struct user),1,f1);    // PANG WRITE  LANG NG BINARY CANCEL MUNA  
            printf("\nSIGN UP SUCCESS\nPRESS ANY KEY TO CONTINUE");
            fclose(f1);
            lb = fopen("leaderb.txt","a");
            strcpy(acc.username,username_checker);
            fprintf(lb, "%s\t%i\n",acc.username, acc.stage);
            fclose(lb);
            getch();
            option = 00;
            system("cls");
            login();
        }
        else{//ascii code of [ESC] is 27
            while(option != 27){ 
                printf("\nPASSWORD DOES NOT MATCH\n\nPress any key to sign up again.\nPress ESC to go back to dashboard\n");
                option = getch();
                if(option == 27) option = 00;
                break;
            }
        }   
            system("cls");
    }while(option!=00);
main(); 
}//END OF SIGNUP FUNCTION//

//LOGIN//
void login(){
    char username_checker[20], password_checker[12];
    struct user account;
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
        while(fscanf(f1,"%s", account.password)){
        //(fread(&account, sizeof(struct user),1,f1)!=EOF){ //PANG READ LANG NG BINARY TO CANCEL MUNA
            if(!strcmp(account.password,password_checker)){
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

            case 27 : //ascii code of [ESC] is 27
            system("cls"); exit(0);

            default: system("cls");
        } //ascii code of [ESC] is 27
    break;
    }
    
}//END OF MENU FUNCTION//

void about(){
    char option, buffer[255];
    FILE *rf;
    do{
    rf = fopen("about1.txt", "r");
    if(rf == NULL) printf("ERROR_FILE_MISSING");
    else{
        while(fgets(buffer,255,rf)!=NULL){
        printf("%s", buffer);
        }
    }
    fclose(rf);
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
    char option,buffer[255];
    struct user acc;
    FILE *f1;
    do{
    printf("LEADERBOARDS\n\n\n");
    for(i = 0; i<25; i++) printf("-");
    printf("\n");
    printf("| NO. | USERNAME | STAGE |");
    printf("\n");
    for(i = 0; i<25; i++) printf("-");
    f1 = fopen("leaderb.txt","r");
    while(fread(&acc,sizeof(struct user),1,f1)){
        //printf("\n%s",acc.username);
        printf("\n%i",acc.stage);
    }
    // while(fgets(buffer,255,f1)){
    //     printf("%s",buffer);
    //     printf("%s\n",acc.username);
    //     printf("%i",acc.stage);
    // }
    fclose(f1);
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
    //char ign[20];
    struct user acc;
    FILE *f1;
    //account.stage=stage_1;
    //printf("%i\n", account.stage); getch(); //wag pansinin wala to. 
    //strcpy(ign,check_filename);
    f1 = fopen(check_filename,"r");
    //printf("%s", check_filename);
    if(f1 == NULL){
    printf("ERROR OPENING FILE");
    fclose(f1);
    }
    else{
        //(fread(&account, sizeof(struct user),1,f1)!=EOF){
        while(!fscanf(f1,"%i", &acc.stage)){
        //while(fgets(buffer,255,rf)!=NULL){    
            //fseek(rf, sizeof(account.username), SEEK_CUR);
            if(acc.stage == stg1){
            printf("STAGE : %i\n", acc.stage); getch(); 
            system("cls"); 
            fclose(f1); stage1(); 

            }
            else if(acc.stage == stg2){
            system("cls");
            printf("STAGE : %i\n", acc.stage);
            fclose(f1); stage2(); 
            //fclose(f1); system("cls"); stage2();
            }
            else{
            fclose(f1);
            printf("STAGE : %i\n", acc.stage);
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

void stage1(){
    int n1, n2, sys_ans, user_ans;
    struct user account;
    FILE *f1;
    srand(time(NULL));
    printf("%s", check_filename);
    while(main_option != 27 && main_option != 'B'){
        printf("STAGE 1\n\n\n");
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
            //if(level > 5) break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
            }while(level<=5);
        printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
        option_prompt();
        if(main_option == 00) {
        break;
        }
    }
    f1 = fopen(check_filename, "w");
    if(f1 == NULL){ 
        printf("ERROR_FETCHING_FILES"); exit(0);
    }
    else{
        //account.stage = stg2;
        //printf("\n%i", account.stage); getch();
        //fseek(f1, sizeof(account.stage), SEEK_END);
        fprintf(f1, "\n%i", account.stage);
        //fwrite(&account, sizeof(account.stage),1,f1);
        fclose(f1);
        }
    stage2();
    }

void stage2(){
    printf("STAGE 2 NA!");
    getch();
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