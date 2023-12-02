#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Function of Operator
int addition(int n1, int n2) {
  return n1 + n2; 
}
int subtraction(int n1, int n2) {
  return n1 - n2; 
}

int counter=0;
void identifier(int a, int b){
    if(a == b){ 
    printf("KORIQUE!!!");
    }
    else if(a != b){
    printf("ENGKK!!");
    counter++;
    }
}
//stage 1 ito
void main(){
    char option;
    srand(time(NULL));
    int n1, n2, sys_ans, user_ans, level=1;

    srand(time(NULL));
    printf("STAGE 1\n\n\n");
    while(option != 27 && option != 'B'){
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
        printf("\nPress any key to continue to the try again.");
        printf("\nPress B to go back to dashboard.");
        printf("\nPress ESC to log out and exit.");
        option = getch();
        option = toupper(option);
            if(option == 27){//ascii code of [ESC] is 27
                exit(0);
            }   
            else if(option == 'B'){
                printf("\nMENU"); break;
            }
            else{
                option = 00; 
                level = 1;
                counter = 0;
                system("cls");
                continue;
            }
        }
        else{
        printf("\nPress any key to continue to the next stage.");
        printf("\nPress B to go back to dashboard.");
        printf("\nPress ESC to log out and exit.");
        option = getch();
        option = toupper(option);
            if(option == 27){//ascii code of [ESC] is 27
                exit(0); break;
            }
            else if(option == 'B'){
                printf("\nMENU"); break;
            }
            else{
                printf("\nSTAGE 2 na par call nalang function"); break;
            }
        }
    }
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