#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//#include "structures.c"
 
void Usertranslog(char c[])//checks for the transaction log of the particular user and prints the details
{
	time_t t=time(NULL);
	struct tm tm=*localtime(&t);
	char Date[15],str[500];
	int i,f=0,x=1;
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
	//printf("%s\n",Date);
	int transid=GenerateTransId(Date);
	FILE *fp1;
	fp1=fopen(Date,"r");
	//itoa(c,user,10);
	printf("%s\n",c);
	if(fp1!=NULL)
	{
		while( fgets(str,500,fp1)!=NULL)
		{
			f=0;
			for(i=0;i<10;i++)
			{
				if(c[i]==str[i])
				{
					//printf("%c%c\n",c[i],str[i]);
					f++;
				}
			}
			if(f==10)
			{
				x=0;
				printf("%s\n",str);
			}

		}
		if(x)
		{
			printf("No Transactions in your Account\n");
		}
		fclose(fp1);
	}
	else
	{
		printf("No Transactions in your Account\n");
	}
}


void updateprofile(USER_ACCOUNTS *current_user,USER_ACCOUNTS *head)//updates profile of the current user
{
	USER_DETAILS user=current_user->user;
	printf("%-30s","ENTER YOUR NAME : ");
	scanf("%s",user.User_Name);
	printf("%-30s","ENTER YOUR AGE : ");
	scanf("%d",&(user.Age));
	current_user->user=user;
	updateInFiles(head);
}

void UserMenu(USER_ACCOUNTS *current_user, USER_ACCOUNTS *head){ //displays all tasks that can be performed by the user after logging in
	system("clear");
	printf("1. Check Account Balance\n");
	printf("2. Deposit Money\n");
	printf("3. Withdraw Money\n");
	printf("4. Transfer Funds\n");
	printf("5. Display Transaction Log\n");
	printf("6. Change Pin\n");
	printf("7. View Profile\n");
	printf("8. Update Profile\n");
	int a;
	char acc[12];
	float cash;
	scanf("%d", &a);

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
	int transid=GenerateTransId(Date);
	//printf("%s\n",Date);
	FILE *fp1;
	fp1=fopen(Date,"a");
	system("clear");

	switch(a){
		case 1: printf("Your Current Account Balance Is %.2f\n",current_user->user.Balance);
			break;
		case 2: printf("Enter The Amount To Be Deposited\n");
			scanf("%f",&cash);	
			Total_Cash+=cash;
			current_user->user.Balance+=cash;
			fprintf(fp1,"%s,%d,%.2f,%s,%d:%d:%d,Credit\n",current_user->user.Acc_No,transid,current_user->user.Balance,current_user->user.User_Name,tm.tm_hour,tm.tm_min,tm.tm_sec);
			updateInFiles(head);
			break;
		case 3: printf("Enter The Amount To Be Withdrawn\n");
			scanf("%f",&cash);
			if(cash<=Transaction_Limit && cash <= Total_Cash && cash <=current_user->user.Balance ){
				Total_Cash-=cash;
				current_user->user.Balance-=cash;
				fprintf(fp1,"%s,%d,%.2f,%s,%d:%d:%d,Debit\n",current_user->user.Acc_No,transid,current_user->user.Balance,current_user->user.User_Name,tm.tm_hour,tm.tm_min,tm.tm_sec);
				updateInFiles(head);	}

			else if(cash >= Total_Cash){
				printf("Cash Not Available In ATM\n");
			}
			else if(cash>=Transaction_Limit){
				printf("You Have Exceeded Your Transaction Limit\n");
			}
			else {
				printf("Insufficient Funds\n");
			}

			break;
		case 4: transferUserFunds(current_user,head);
			break;	
		case 5:
			Usertranslog(current_user->user.Acc_No);
			break;
		case 6: changepin(current_user,head);
			break;	
		case 7 :viewprofile(current_user);
			break;
		case 8: updateprofile(current_user,head);
			break;


	}
	fclose(fp1);

} 
