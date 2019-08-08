#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "structures.c"

float Total_Cash,Transaction_Limit = 20000;
char AdminAcc[12] = "0000000000";
int AdminPin = 0000;

#include "035-assign12.c"
#include "082-assign12.c"
#include "104-assign12.c"
#include "055-assign12.c"

int main(){
	system("clear");
	USER_ACCOUNTS *head = NULL;
	head = insertUserDataFromFile(head);
	printf("_________________WELCOME TO__________________\n\n");
	printf("__________ULTIMATE CODERS BANK ATM___________\n\n");
	printf("______________SRI CITY BRANCH________________\n\n");
	printf("__________DAILY LIMIT = Rs.20000_____________\n\n");
	Execution(head);
return 0;
}
