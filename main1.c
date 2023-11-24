#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Function of Operator 
int addition(int n1, int n2);
float  subtraction(float n1, float n2);
float multiplication(float n1, float n2);
float division(float n1, float n2);


//Wrong or correct identifier
void identifier(int n1, int n2);

typedef struct {
 int level;
 int stage;
}progress;

int main(){
int n1, n2, system_ans, user_ans;
int  opPicker;
    
    progress mode;
    mode.stage = 1;
    mode.level = 1;

    srand(time(NULL));
    while(mode.stage != 5){
        printf("Stage %d\n", mode.stage);
        printf("_______________________\n\n");
        if(mode.stage == 1){
            while(mode.level <= 2){
                
                printf("Level %d\n", mode.level);
                    n1 = (rand() % 25) + 1;
                    n2 = (rand() % 25) + 1;
                if(mode.level == 1){
                    n1 + 10;
                    n2 + 10;
                }
                else if(mode.level == 2){
                    n1 = (rand() % 100) + 1;
                    n2 = (rand() % 100) + 1;
                }
                system_ans = addition(n1, n2);
                printf("%d + %d = ", n1, n2);
                scanf("%d", &user_ans);
                identifier(user_ans, system_ans);
                mode.level++;    
            }
            while(mode.level > 2 && mode.level <= 5){
                printf("Level %d\n", mode.level);
                if(mode.level  <= 4){
                    n1 = (rand() % 75) + 1;
                    n2 = (rand() % 75) + 1;
                }
                else if(mode.level == 5){
                    n1 = (rand() % 100) + 1;
                    n2 = (rand() % 100) + 1;
                }
                system_ans = subtraction(n1, n2);
                printf("%d - %d = ", n1, n2);
                scanf("%d", &user_ans);
                identifier(user_ans, system_ans);
                mode.level++;
            }
        }
        mode.stage++;
        mode.level = 1;
        if(mode.stage == 2){
            printf("Stage %d\n", mode.stage);
            printf("_______________________\n\n");
            while(mode.level <= 5){
                printf("Level %d\n", mode.level);
                if(mode.level == 1){
                    n1 = (rand() % 10) + 1;
                    n2 = (rand() % 10) + 1;
                }
                else if(mode.level == 2){
                    n1 = (rand() % 20) + 1;
                    n2 = (rand() % 20) + 1;
                }
                else if(mode.level == 3){
                    n1 = (rand() % 50) + 1;
                    n2 = (rand() % 50) + 1;
                }
                
                else if(mode.level >= 4 && mode.level <= 5){
                    n1 = (rand() % 100) + 1;
                    n2 = (rand() % 100) + 1;
                }
                system_ans = multiplication(n1, n2);
                printf("%d x %d = ", n1, n2);
                scanf("%d", &user_ans);
                identifier(user_ans, system_ans);
                mode.level++; 
            }
        }
        mode.stage++;
    }

   
      


return 0;
}

//Wrong or Correct Identifier
void identifier(int x, int y)
{
    if(x == y){
        printf("Correct\n\n");
    }
    else if(x != y){
        printf("Wrong\n\n");
    }
}

//Function of Operator 
int addition(int n1, int n2)
{
    int result = n1 + n2;
    return result;
}
float  subtraction(float n1, float n2)
{
    return n1 - n2;
}
float multiplication(float n1, float n2)
{
   return  n1 * n2; 
}
float division(float n1, float n2){
   return n1 / n2;
}
   

   

    
//for loop for score counter (for loop ++)
//Show numbers ng mali (for loop i++)
//Option if you want to continue or nah (if else)
//stage 2 (multiplication) 
  /*if(stage == stagelimit){
    printf("you are now in the next Stage");
  }
  stage = stage - 5;
*/
//stage 3 (division)
//stage 4 (add, sub)
//stage 5 (multi, divide)
//last stage (all opp)
//Option to exit game (if else)
//Option to practice again (if else)
//leaderboards 