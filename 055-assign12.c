#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//#include "structures.c"

void userLogin(USER_ACCOUNTS *head){ // this function verifies the login credentials and calls the corresponding fuctions depending on whether it is admin or user
	char acc[12];
	int pin,flag = 0,flag2 = 0;
	USER_ACCOUNTS *temp = head;
	USER_ACCOUNTS *send = head;
	printf("ACCOUNT NO. :- ");
	scanf("%s",acc);
	system("clear");
	if(strcmp(acc,AdminAcc)==0){
		printf("Hello Admin, Enter Your Pin No.\n");
		scanf("%d",&pin);
		if(pin == AdminPin){
			printf("Admin Successfully Logged In\n");
			AdminMenu(send);
		}
		if(pin != AdminPin){
			printf("Wrong Pin, Insert Your Card Again\n");
		}
	}
	else{
		while(head){
			if(strcmp(head->user.Acc_No,acc)==0){
				flag = 1;
				printf("Hello %s\n",head->user.User_Name);
				break;
			}
			head= head->next;
		}
		if(flag == 0){
			printf("Wrong Account Number, Insert Your card Again\n");
		}
		if(flag == 1 && !head->user.Block_Status){
			printf("PIN :- ");
			scanf("%d",&pin);
			while(temp){
				if(temp->user.Pin == pin){
					printf("Successfully Logged In\n");
					flag2 = 1;
					UserMenu(temp,send);
				}
				temp = temp->next;
			}
			if(flag2 == 0){
				printf("Wrong Pin, Insert Your Card Again");
			}
		}
		if(flag == 1 && head->user.Block_Status){
			printf("You Are Currently Blocked By The Bank\n");
		}
	}

}

USER_ACCOUNTS *createNewAccount(USER_ACCOUNTS *head){ // creates a new account with acc.no from new accounts file adds to the user details file
	FILE *fp1 = fopen("new_account.txt","r");
	NEW_USER_LL *new_head = NULL,*to_save;
	char str[200],A[10][50];
	while(fscanf(fp1,"%s",str)>=1){
		NEW_USER_LL *new = (NEW_USER_LL *)malloc(sizeof(NEW_USER_LL));
		int i,j=0,k=0;
		for(i=0;i<strlen(str);i++)
		{
			if(str[i]==','||str[i]=='\0'||str[i]=='\n')
			{
				A[j][k++]='\0';
				k=0;
				j++;
			}
			else
			{
				A[j][k++]=str[i];
			}
		}
		int a;
		strcpy(new->user.Acc_No,A[0]);
		new->user.OTP = atoi(A[1]);
		new->next = new_head;
		new_head = new;
		//printf("%d\n",head->user.Pin);
	}
	fclose(fp1);
	to_save = new_head;
	new_head = new_head->next;
	FILE *fp2 = fopen("new_account.txt","w");
	while(new_head){
		fprintf(fp2,"%s,%d\n",new_head->user.Acc_No,new_head->user.OTP);
		new_head = new_head->next;
	}
	fclose(fp2);
	printf("Hello New User, Your New Account No. is %s\nPlease Enter The OTP You received To Proceed Further\n",to_save->user.Acc_No);
	int otp;
	scanf("%d",&otp);
	system("clear");
	if(otp != to_save->user.OTP){
		printf("You Have Entered The Wrong OTP\n");
		FILE *fp3 = fopen("new_account.txt","a+");
		fprintf(fp3,"%s,%d",to_save->user.Acc_No,to_save->user.OTP);
		fclose(fp3);
	}
	else{
		USER_ACCOUNTS *new_user = (USER_ACCOUNTS *)malloc(sizeof(USER_ACCOUNTS));
		printf("Enter Your Name\n");
		scanf("%s",new_user->user.User_Name);
		printf("Enter Your Age\n");
		scanf("%d",&new_user->user.Age);
		strcpy(new_user->user.Acc_No,to_save->user.Acc_No);
		new_user->user.OTP = to_save->user.OTP;
		printf("Enter Your 4 Digit Pin\n");
		scanf("%d",&new_user->user.Pin);
		new_user->user.Block_Status = 0;
		printf("Enter The Balance You Want To Enter\n");
		scanf("%f",&new_user->user.Balance);
		Total_Cash+=new_user->user.Balance;
		//new_user->user.Balance+=cash;
		new_user->next = head;
		head = new_user;
		printf("Congrats, Your Account Has Been Created\n");
		updateInFiles(head);
	}


}
 
void Execution(USER_ACCOUNTS *head){ // displays the main menu and helps navigate to user or create account functions.
	printf("1. Already A User, Login\n");
	printf("2. Not A User, Create An Account\n");
	int temp;
	scanf("%d",&temp);
	system("clear");
	if(temp == 1){userLogin(head);}else if(temp == 2){createNewAccount(head);}else{printf("Invalid Option, Insert Your Card Again\n");}
}

