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

int counter=0, level=1;

char MW_OPTION, check_filename[20], lb_username[20];
const char stg_1 = '1', stg_2='2', stg_3='3', stg_4='4', stg_5='5', stg_godMode='6';

char USERNAME[50],PASSWORD[20];
char ACCOUNT_STAGE[1];

typedef struct {
    char line[100];
}Line;

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

// void updateStage(const char *username, const char *newStage, const char *filePath);
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
float DO_ROUND(float num) {
     if(num>=0) return (int)(num + 0.5); else return (int)(num - 0.5);
}

//Function for Round OFF
float round_off(float value, int decimal_places)
{
  float rounded;
  float shift = pow(10, decimal_places);
  rounded = value * shift;
  rounded = DO_ROUND(rounded);
  rounded = rounded / shift;
return rounded;
}

//Correct or Wrong Identifier
void identifier(int a, int b){//for int
    if(a == b){
    textcolor(GREEN); cprintf("CORRECT!!!"); textcolor(WHITE);
    }
    else if(a != b){
    textcolor(RED); cprintf("INCORRECT!!!"); textcolor(WHITE);
    counter++;
    }
}
void fIdentifier(float a, float b, float c){// for point decimals, [FLOAT]
    if(a == b || a == c){
    textcolor(GREEN); cprintf("CORRECT!!!"); textcolor(WHITE);
    }
    else if(a != b || a != c){
    textcolor(RED); cprintf("INCORRECT!!!"); textcolor(WHITE);
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
    int i;
    char option;
    clrscr();
    //dashboard//
    do{ //ASCII CODE [1] is 49, [2] is 50, [3] is 51//
    gotoxy(58,24);
    textcolor(184);
    cprintf("\xdb MADE BY COLMO & MANIT");
    gotoxy(2,4);
    for(i=1;i<40;i++) printf("\x4 ");
    textcolor(21);
    gotoxy(21,5);
    cprintf("\x4 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 MATH WHIZ \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \x4\n");
    gotoxy(2,6);
    for(i=1;i<40;i++) printf("\x4 ");
    gotoxy(33,12);
    textcolor(YELLOW);
    cprintf("\x9 [1] LOG IN   \x10");
    gotoxy(33,13);
    textcolor(GREEN);
    cprintf("\x9 [2] SIGN UP  \x10");
    gotoxy(28,20);
    textcolor(WHITE);
    cprintf("\xae \x9 PRESS ESC TO EXIT \x9 \xaf");
    gotoxy(30,22);
    textcolor(WHITE);
    option = getch();
	switch(option){
	    case '1' : login();  break;
	    case '2' : signup(); break;
	    case ESC : clrscr(); break;
	    default  : cprintf("INVALID KEY SELECTION"); getch();
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
	gotoxy(18,7);
	printf("SIGN UP");
	gotoxy(18,11);
	printf("Enter preferred username:  ");
	scanf("%s", username_checker);
	gotoxy(18,12);
	printf("Enter preferred password:  ");
	hide_input(password_checker);
	gotoxy(18,13);
	printf("Repeat preferred password: ");
	hide_input(confirm_password);
	strcpy(file_name, username_checker);
	fr = fopen(strcat(file_name,".dat"),"r");
	//printf("\n%s",check_filename);getch();
	if(fr == NULL){
	    if(!strcmp(password_checker, confirm_password)){
		fclose(fr);
		ACCOUNT_STAGE[0] = stg_1;
		strcpy(USERNAME,username_checker);
		strcpy(PASSWORD,password_checker);
		fw = fopen(file_name,"w");
		fprintf(fw, "%s %s %c\n",USERNAME,PASSWORD,ACCOUNT_STAGE[0]);
		fclose(fw);
		//-----------------------------------
		lb = fopen("LEADERB.txt","a");
		fprintf(lb, "%s  %c\n",USERNAME,ACCOUNT_STAGE[0]);
		fclose(lb);
		gotoxy(18,15);
		textcolor(LIGHTGREEN);
		cprintf("SIGN UP SUCCESS");
		gotoxy(25,20);
		textcolor(14);
		cprintf("PRESS ANY KEY TO CONTINUE");
		textcolor(WHITE);
		option = 00; getch(); clrscr(); login();
	    }
	    else{//ascii code of [ESC] is 27
		while(option!=ESC){
		    gotoxy(18,16);
		    textcolor(RED);
		    cprintf("PASSWORD DOES NOT MATCH");
		    gotoxy(25,20);
		    textcolor(14);
		    cprintf("Press any key to sign up again");
		    gotoxy(23,21);
		    textcolor(14);
		    cprintf("Press ESC to go back to dashboard");
		    textcolor(WHITE);
		    option = getch();
		    if(option == ESC) option = 00;
		    break;
		}
	    }
	}
	else{
	    option = 00;
	    gotoxy(18,16);
	    textcolor(RED);
	    cprintf("USERNAME ALREADY EXIST"); getch();
	    textcolor(WHITE);
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

    gotoxy(18,7);
    printf("LOG IN");
    gotoxy(18,11);
    printf("Enter username:  ");
    scanf("%s", username_checker);
    gotoxy(18,12);
    printf("Enter password:  ");
    hide_input(password_checker);
    //scanf("%s", &password_checker);
    strcpy(check_filename,username_checker); //check_filename ay global variable
    //printf("%s", check_filename); getch(); this line was only for checking the string value of username
    fr = fopen(strcat(check_filename,".dat"),"r");
    if(fr == NULL){
	fclose(fr);
	gotoxy(18,14);
	textcolor(LIGHTRED);
	cprintf("USER DOES NOT EXIST"); getch();
	textcolor(WHITE);
	clrscr();
	main();
    }
    else{
	//(fscanf(f1,"%s", account.password)!=EOF){
	while(fscanf(fr, "%s %s %c\n",USERNAME,PASSWORD,ACCOUNT_STAGE)!=EOF){ //READ BINARY FROM FILE
	    if(!strcmp(PASSWORD,password_checker)){
		strcpy(lb_username,username_checker);
		//printf("\nUSERNAME : %s", USERNAME);
		//printf("\nPASSWORD : %s", PASSWORD);
		//printf("\nSTAGE : %c", ACCOUNT_STAGE[0]);
		fclose(fr);
		clrscr(); menu(); break;
	    }
	    else{
		fclose(fr);
		// printf("\nUSERNAME : %s", USERNAME);
		// printf("\nPASSWORD : %s", PASSWORD);
		// printf("\nPASSWORD : %s", ACCOUNT_STAGE);
		gotoxy(18,14);
		textcolor(LIGHTRED);
		cprintf("INCORRECT PASSWORD");getch();
		textcolor(WHITE);
		clrscr(); main(); break;
	    }
	}
    }
}//END OF LOGIN FUNCTION//

//MENU FUNCTION//
void menu(){
    int i;
    char option;

    while(option!='P' && option!='L' && option!='A' && option!= ESC){
	gotoxy(2,4); for(i=1;i<40;i++) printf("\x4 ");
	textcolor(21); gotoxy(21,5);
	cprintf("\x4 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 MATH WHIZ \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \xB1 \x4\n");
	gotoxy(2,6); for(i=1;i<40;i++) printf("\x4 ");
	gotoxy(32,10); textcolor(LIGHTGREEN); cprintf("[P] START");
	gotoxy(32,11); textcolor(GREEN); cprintf("[L] LEADERBOARDS");
	gotoxy(32,12); textcolor(7); cprintf("[A] ABOUT");
	gotoxy(27,20); textcolor(WHITE); cprintf("\xae \x9 Press ESC to go back \x9 \xaf");
	gotoxy(31,22); textcolor(WHITE);
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

	    default: printf("INVALID KEY SELECTION"); getch(); clrscr();
	}
    }

}//END OF MENU FUNCTION//

void about(){
    char option, BUFFER_FCONTENT[256];
    FILE *fr;

    //int MAX_BUFFER_LINE = sizeof(BUFFER_FCONTENT);
    //printf("SIZE %d", MAX_BUFFER_LINE); getch(); THIS LINE AY ONLY FOR CHECKING OF BUFFER VALUE IN BYTES
    do{
	/*fr = fopen("about1.txt", "r");
	if(fr == NULL) printf("ERROR_FILE_MISSING");
	else{
	    while(fgets(BUFFER_FCONTENT,MAX_BUFFER_LINE,fr)!=NULL)
	    printf("%s", BUFFER_FCONTENT);
	}
	fclose(fr);
	*/
	gotoxy(58,24);textcolor(184); cprintf("\xdb MADE BY COLMO & MANIT");
	gotoxy(32,3); textcolor(YELLOW); cprintf("\x4 ABOUT MATH WHIZ \x4");
	gotoxy(5,6);
	printf("Math Whiz is not only a game; it's a challenging adventure through solving and overcome every stages and levels without having an incorrect answers.");
	gotoxy(74,7);
	printf("That puts your intuition and critical thinking to the test. This simple solving game promises a delish user interface and user experience.");
	gotoxy(28,20); textcolor(WHITE); cprintf("\xae \x9 Press ESC to go back \x9 \xaf");
	option = getch();
	option = toupper(option);
	clrscr();
    }while(option!=ESC); //ascii code of [ESC] is 27.
    clrscr();
    menu();
}
//LEADERBOARDS// di maka handle ng long usernames na pwede maglead sa unresponsiveness
void leaderboards(){
    int i, lineLB=0;
    char option, tmp = ' ';
    FILE *fr;
    do{
	gotoxy(32,3); textcolor(GREEN); cprintf("\xB2\xB2\xB2 LEADERBOARDS \xB2\xB2\xB2");
	gotoxy(2,5); for(i = 0; i<75; i++) printf("=");
	gotoxy(2,6); printf("\xdd NO. \xdd  USERNAME %39c \xdd %4cSTAGE \%4c\xdd",tmp,tmp,tmp);
	gotoxy(2,7); for(i = 0; i<75; i++) printf("=");
	fr = fopen("LEADERB.txt", "r");
	while(fscanf(fr,"%s  %c\n",USERNAME,ACCOUNT_STAGE)!=EOF){
	    lineLB++;
	    printf("\n  %2i.",lineLB);
	    textcolor(LIGHTGREEN);cprintf("  %10s",USERNAME);
	    textcolor(YELLOW);cprintf("%52c",ACCOUNT_STAGE[0]);
	    printf("\n ---------------------------------------------------------------------------");
	    textcolor(WHITE);
	}
	lineLB=0;
	fclose(fr);
	gotoxy(28,23); textcolor(WHITE); cprintf("\xae \x9 Press ESC to go back \x9 \xaf");
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
	while(fscanf(fr,"%s %i\n",&USERNAME,&ACCOUNT_STAGE)==1){
	    if(ACCOUNT_STAGE[0] == stg_1){
		fclose(fr); clrscr(); stage1(); break;
	    }
	    else if(ACCOUNT_STAGE[0] == stg_2){
		fclose(fr); clrscr(); stage2(); break;
	    }
	    else if(ACCOUNT_STAGE[0] == stg_3){
		fclose(fr); clrscr(); stage3(); break;
	    }
	    else if(ACCOUNT_STAGE[0] == stg_4){
		fclose(fr); clrscr(); stage4(); break;
	    }
	    else if(ACCOUNT_STAGE[0] == stg_5){
		fclose(fr); clrscr(); stage5(); break;
	    }
	    else if(ACCOUNT_STAGE[0] == stg_godMode){
		fclose(fr); clrscr(); final_stage(); break;
	    }
	    else{
		fclose(fr);
		printf("ERROR ON ALLOCATING OF LOADED PROGRESS");
		getch(); exit(1);
	    }
	}
    }
}//END OF MATH WHIZ//

void option_prompt(){
    gotoxy(35,10);textcolor(YELLOW);cprintf("\x10 YOU HAVE %i INCORRECT ANSWERS", counter);
    if(counter > 0){
    gotoxy(35,12);textcolor(LIGHTRED);cprintf("\x9 Press any key to TRY AGAIN.");
    gotoxy(35,13);textcolor(7);cprintf("\x9 Press [B] to go back to MENU.");
    gotoxy(35,14);textcolor(WHITE);cprintf("\x9 Press ESC to EXIT & LOG OUT.");
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
    gotoxy(35,12);textcolor(LIGHTRED);cprintf("\x9 Press any key to TRY AGAIN.");
    gotoxy(35,13);textcolor(7);cprintf("\x9 Press [B] to go back to MENU.");
    gotoxy(35,14);textcolor(WHITE);cprintf("\x9 Press ESC to EXIT & LOG OUT.");
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
    char *newSTG;
    // int structIndex=1;
    // long offset = sizeof(ACCOUNT_STAGE) * structIndex;
    strcpy(ign,lb_username);
    //strcpy(loc_acc.username,ign);
    srand(time(NULL));
    //printf("\n%s", check_filename); .dat
    //printf("\n%s", loc_acc.username);
    //printf("\n%s", ign);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
	gotoxy(33,2);printf("\x11 STAGE %c \x10",ACCOUNT_STAGE[0]);
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
	*newSTG = ACCOUNT_STAGE[0];
	fseek(fw, -3, SEEK_END);
	fprintf(fw,"%c", ACCOUNT_STAGE[0]);
	fclose(fw);
    }
    //updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,newSTG,"LEADERB.txt");
stage2();
}

void stage2(){ //MULTIPLICATION
    int n1, n2, sys_ans, user_ans;
    FILE *fw;
    char ign[20];
    char *newSTG;

    strcpy(ign,lb_username);
    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
	gotoxy(33,2);printf("\x11 STAGE %c \x10",ACCOUNT_STAGE[0]);
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
	*newSTG = ACCOUNT_STAGE[0];
	fseek(fw, -3, SEEK_END);
	fprintf(fw,"%c", ACCOUNT_STAGE[0]);
	fclose(fw);
    }
    // updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,newSTG,"LEADERB.txt");
stage3();
}

void stage3(){ //DIVISION
    float n1, n2, sys_ans1, sys_ans2, user_ans;
    FILE *fw;
    char ign[20];
    char *newSTG;

    strcpy(ign,lb_username);
    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
	gotoxy(33,2);printf("\x11 STAGE %c \x10",ACCOUNT_STAGE[0]);
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
	*newSTG = ACCOUNT_STAGE[0];
	fseek(fw, -3, SEEK_END);
	fprintf(fw,"%c", ACCOUNT_STAGE[0]);
	fclose(fw);
    }
    // updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,newSTG,"LEADERB.txt");
stage4();
}

void stage4(){ //MIXED OF ADDITION AND SUBTRACTION
    int n1, n2, n3, sys_ans, user_ans;
    FILE *fw;
    char ign[20];
    char *newSTG;

    strcpy(ign,lb_username);
    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
	gotoxy(33,2);printf("\x11 STAGE %c \x10",ACCOUNT_STAGE[0]);
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
	*newSTG = ACCOUNT_STAGE[0];
	fseek(fw, -3, SEEK_END);
	fprintf(fw,"%c", ACCOUNT_STAGE[0]);
	fclose(fw);
    }
    // updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,newSTG,"LEADERB.txt");
stage5();
}

void stage5(){ //MIXED OF MULTIPLICATION AND DIVISION
    float n1, n2, n3, sys_ans1, sys_ans2, user_ans;
    FILE *fw;
    char ign[20];
    char *newSTG;

    strcpy(ign,lb_username);
    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
	gotoxy(33,2);printf("\x11 STAGE %c \x10",ACCOUNT_STAGE[0]);
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
	*newSTG = ACCOUNT_STAGE[0];
	fseek(fw, -3, SEEK_END);
	fprintf(fw,"%c", ACCOUNT_STAGE[0]);
	fclose(fw);
    }
    // updateStage(ign,ACCOUNT_STAGE,"LEADERB.txt");
    updateAndSort(ign,newSTG,"LEADERB.txt");
final_stage();
}

void final_stage(){ //MIXED OF ALL OPERATORS
    float n1, n2, n3, n4, n5, sys_ans1, sys_ans2, user_ans;

    srand(time(NULL));
    //printf("%s", check_filename);
    while(MW_OPTION != ESC && MW_OPTION != 'B'){
	gotoxy(33,2);printf("\x11 FINAL STAGE \x10");
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

int compareStages(const void *a, const void *b) {
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
	    fprintf(stderr, "Too many lines in the file.");
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
    qsort(lines, lineCount, sizeof(Line), compareStages);
    fseek(fr, 0, SEEK_SET);
    for (i = 0; i < lineCount; i++) {
	fputs(lines[i].line, fr);
    }
    fclose(fr);
}
// void updateStage(const char *username,const char newStage[1], const char *filePath){
//     char BUFFER[100];
//     FILE *fr = fopen(filePath, "r+");

//     if (fr == NULL) {
// 	perror("Error opening file");
// 	exit(EXIT_FAILURE);
//     }
//     while (fgets(BUFFER, sizeof(BUFFER), fr) != NULL) {
// 	if (strstr(BUFFER, username) != NULL) {
// 	    //snprintf(BUFFER, sizeof(BUFFER), "%s %s\n", username, newStage);
// 	    sprintf(BUFFER,"%s %c\n",username, newStage);
// 	    fseek(fr, (-strlen(BUFFER)-1), SEEK_CUR);
// 	    fputs(BUFFER, fr);
// 	    break;
// 	}
//     }
//     fclose(fr);
// }