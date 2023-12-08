#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int counter=0, level=1;
char main_option;
// Function of Operator
int addition(int n1, int n2) {
  return n1 + n2; 
}
int subtraction(int n1, int n2) {
  return n1 - n2; 
}

float divide(float n1, int n2){
  return n1 / n2;
}


void identifier(double a, double b){
    if(a == b){ 
    printf("KORIQUE!!!");
    }
    else if(a != b){
    printf("ENGKK!!");
    counter++;
    }
}
void identifier_1(int a, int b){
    if(a == b){ 
    printf("KORIQUE!!!");
    }
    else if(a != b){
    printf("ENGKK!!");
    counter++;
    }
}

void stage1();
void stage2();

void decision_prompt(){
   if(counter > 0){
    printf("\nPress any key to try again.");
    printf("\nPress [B] to go back to dashboard.");
    printf("\nPress ESC to log out and exit.");
    main_option = getch();
    main_option = toupper(main_option);
      switch(main_option){    
      case 27 ://ascii code of [ESC] is 27
      exit(0);

      case 'B' : //Press B to go back to MENU
      printf("\nMENU"); break;

      default : //press any key to try again
      main_option = 00; level = 1; counter = 0;
      system("cls"); 
      }    
    }
    else{
    printf("\nPress any key to continue to the next stage.");
    printf("\nPress [B] to go back to dashboard.");
    printf("\nPress ESC to log out and exit.");
    main_option = getch();
    main_option = toupper(main_option);
      switch(main_option){
      case 27 : //ascii code of [ESC] is 27
      exit(0);

      case 'B' : //Press B to go back to dashboard
      main_option  = 00; level = 1; counter = 0;
      system("cls"); printf("\nDSAHBOARD");

      default : //Press any key to continue
      main_option = 00; level = 1; counter = 0;
      system("cls"); printf("\nSTAGE 2"); break;
      }
    } 
}

//stage 1 ito
void main(){
    srand(time(NULL));
    int n1, n2, sys_ans, user_ans;

    srand(time(NULL));
    
    do{
    printf("STAGE 1\n\n\n");
    while(level<=5){
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
    }
    printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
    decision_prompt();//PROMPTS AN OPTION WHETHER IF THE USER HAD WRONG OR NO WRONG ANSWERS.
    if(main_option = 00); break;
    }while(main_option != 27 && main_option != 'B');
stage2();
}

void stage2(){ //DIVISION
    int n1, n2;
    float sys_ans, user_ans;
    srand(time(NULL));
    while(main_option != 27 && main_option != 'B'){
        printf("STAGE 2\n");
        do{
            n1 = (rand() % 10) + 1;
            n2 = (rand() % 10) + 1;
            printf("\n\nLEVEL %i\n",level);
            sys_ans = divide(n1,n2);
            printf("bot ans: %f\n", sys_ans);
            printf("%d ÷ %d = ", n1, n2);
            scanf("%f", &user_ans);
            identifier_1(user_ans, sys_ans);
            level++;
            //if level > 5 break; AUTO BREAK NA YUNG WHILE LOOP KAPAG LUMAGPAS SA LEVEL 5
        }while(level<=5);
        printf("\n\nYOU HAVE %i WRONG ANSWERS", counter);
        decision_prompt();
    } 
        //PROCEED SA NEXT STAGE PAG NAGBREAK, ELSE ULIT STAGE
    printf("stage3");
}
/*

Stage 1
level 1 correct 
level 2 correct
level 3 correct
level 4 correct
level 5 wrong

-YOU HAVE 1 WRONG ANSWERS-

Press SPACEBAR to try again.
Press B to go back to menu
Press ESC to log out and exit
---------------------------------

Stage 1
level 1 correct 
level 2 correct
level 3 correct
level 4 correct
level 5 correct

-YOU HAVE 0 WRONG ANSWERS-

Press SPACEBAR to continue to the next stage.
Press B to go back to dashboard
Press ESC to log out and exit
*/