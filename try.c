#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
    struct details{
        char username[20];
        char password[12];
    }DTLs[2];

    struct progress{
        int stage;
        int level;
    }prog[2];
}User;

void titlemain();
//void math_whiz();
//void sign_up();
//void log_in();

int mainclone()
{
    int select;
    User s1;
    do{

        title();

        printf("[1] LOG IN\n");
        printf("[2] SIGN UP\n");
        printf("[3] ABOUT US\n");
        printf("[4] EXIT\n");
        printf("Select :\t");
        scanf("%d", &select);
        switch(select){

            case 1 : //log in
                printf("LOGIN");
            break;

            default : break;
        }

    }while(select != 4);


return 0;
}

void titlemain()
{
    printf("MATH WHIZ");
    printf("\n\n\n\n\\n");
}
