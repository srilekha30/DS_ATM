#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
typedef struct user_details{
	char Acc_No[12],User_Name[30];
	int Pin,OTP,Age;
	float Balance;
	bool Block_Status;
}USER_DETAILS;

typedef struct user_accounts{
	USER_DETAILS user;
	struct user_accounts *next;
}USER_ACCOUNTS;

typedef struct new_user_details{
	char Acc_No[12];
	int OTP;
}NEW_USER_DETAILS;

typedef struct new_user_ll{
	NEW_USER_DETAILS user;
	struct new_user_ll *next;
}NEW_USER_LL;
