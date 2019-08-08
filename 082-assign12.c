#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//#include "structures.c"


void AdminMenu(USER_ACCOUNTS *head){ // this functions shows all the tasks that can be performed as Admin
	system("clear");
	printf("1. Remove An User Account\n");
	printf("2. Block/Unblock A User\n");
	printf("3. Load Cash Into ATM\n");
	printf("4. ATM Transaction Log\n");
	printf("5. Display All Account Details\n");
	int a;
	char acc[12];
	float cash;
	scanf("%d",&a);
	system("clear");
	switch(a){
		case 1: printf("Enter The Account No. To Remove\n");
			scanf("%s",acc);
			removeAccount(head,acc);
			break;
		case 2: printf("Enter The Account No. To Change Block Status\n");
			scanf("%s",acc);
			changeBlockStatus(head,acc);
			break;	
		case 3: printf("Enter The Amount To Be Loaded In The ATM\n");
			scanf("%f",&cash);
			Total_Cash+=cash;
			printf("Available Cash In The ATM is %.2f\n",Total_Cash);
			FILE *fp1 = fopen("Total_Cash.txt","w");
			fprintf(fp1,"%f",Total_Cash);
			fclose(fp1);
			break;
		case 4:
			ATMTranslog();
			break;
		case 5: printAccountDetails(head);
			break;					 
	}

}

void updateInFiles(USER_ACCOUNTS *head){ //it overwrites the userdetails file and also the totalcash file
	USER_ACCOUNTS *trav2 = head;
	FILE *fp1 = fopen("user_details.txt","w");
	while(trav2){
		fprintf(fp1,"%s,%d,%d,%.2f,%s,%d,%d\n",trav2->user.Acc_No,trav2->user.Pin,trav2->user.OTP,trav2->user.Balance,trav2->user.User_Name,trav2->user.Age,trav2->user.Block_Status);
		trav2 = trav2->next;
	}
	fclose(fp1);
	FILE *fp2 = fopen("Total_Cash.txt","w");
	fprintf(fp2,"%.2f",Total_Cash);
	fclose(fp2);
}




int GenerateTransId(char d[])//used to generate transactionid for each transaction in transaction log file
{
	FILE *fp1=fopen(d,"r");
	int t=1;

	if(fp1!=NULL)
	{
		char str[500];
		while( fgets(str,500,fp1)!=NULL)
		{
			t++;
		}
		fclose(fp1);
	}
	return t;
}	
void transferUserFunds(USER_ACCOUNTS *current_user, USER_ACCOUNTS *head){ //transfers funds from current user to beneficiary account and adds two transactions to transaction log(debit and credit)
	printf("Enter The Beneficiary Account No.\n");
	char acc[12];
	int flag = 0;
	scanf("%s",acc);
	USER_ACCOUNTS *trav = head;

	time_t t=time(NULL);
	struct tm tm=*localtime(&t);
	char Date[15];
	Date[0]=((tm.tm_mday)/10)+48;
	Date[1]=((tm.tm_mday)%10)+48;
	Date[2]='-';
	Date[3]=((tm.tm_mon+1)/10)+48;
	Date[4]=((tm.tm_mon+1)%10)+48;
	Date[5]='-';
	Date[6]=((tm.tm_year+1900)/1000)+48;
	Date[7]=(((tm.tm_year+1900)/100)%10)+48;
	Date[8]=(((tm.tm_year+1900)/10)%10)+48;
	Date[9]=((tm.tm_year+1900)%10)+48;
	Date[10]='.';
	Date[11]='t';
	Date[12]='x';
	Date[13]='t';
	Date[14]='\0';
	FILE *fp1;
	int transid=GenerateTransId(Date);
	fp1=fopen(Date,"a");
	while(trav){
		if(strcmp(trav->user.Acc_No,acc) == 0){
			flag = 1;
			break;
		}
		trav = trav->next;
	}
	if(flag == 1){
		printf("Enter The Amount To Be Transferred\n");
		float a;
		scanf("%f",&a);
		if(current_user->user.Balance>a)
		{
			current_user->user.Balance-=a;
			trav->user.Balance+=a;

			fprintf(fp1,"%s,%d,%.2f,%s,%d:%d:%d,Debit\n",current_user->user.Acc_No,transid,current_user->user.Balance,current_user->user.User_Name,tm.tm_hour,tm.tm_min,tm.tm_sec);
			fprintf(fp1,"%s,%d,%.2f,%s,%d:%d:%d,Credit\n",trav->user.Acc_No,transid+1,trav->user.Balance,trav->user.User_Name,tm.tm_hour,tm.tm_min,tm.tm_sec);
			printf("Succcessfully Transfered Funds\n");

			updateInFiles(head);
		}
		else
		{
			printf("Insufficient Funds\n");
			fprintf(fp1,"%s,%d,%.2f,%s,%d:%d:%d,Transaction Failed\n",current_user->user.Acc_No,transid,current_user->user.Balance,current_user->user.User_Name,tm.tm_hour,tm.tm_min,tm.tm_sec);
		}
	}
	else{

		printf("You Have Entered The Wrong Account No.\n");
	}
	fclose(fp1);
}
void changepin(USER_ACCOUNTS *current_user,USER_ACCOUNTS *head)//changes pin of the current user
{
	printf("%-30s","PLEASE ENTER THE NEW PIN : ");
	scanf("%d",&(current_user->user.Pin));
	updateInFiles(head);
}
void viewprofile(USER_ACCOUNTS *current_user)//profile of current user
{
	USER_DETAILS user=current_user->user;
	printf("%-30s %s\n","NAME :",user.User_Name);
	printf("%-30s %d\n","AGE :",user.Age);
	printf("%-30s %.2f\n","AVAILABLE BALANCE :",user.Balance);
	printf("%-30s %s\n","ACCOUNT NUMBER :",user.Acc_No);
}
