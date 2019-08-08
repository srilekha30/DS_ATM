#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//#include "structures.c"

USER_ACCOUNTS *insertUserDataFromFile(USER_ACCOUNTS *head){ //This function reads the user details from the file ”user_details.txt” and makes a linked list
	FILE *fp1 = fopen("user_details.txt","r");
	char str[200],A[10][50];
	while(fscanf(fp1,"%s",str)>=1){
		USER_ACCOUNTS *new = (USER_ACCOUNTS *)malloc(sizeof(USER_ACCOUNTS));
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
		new->user.Pin = atoi(A[1]);
		new->user.OTP = atoi(A[2]);
		new->user.Balance = atof(A[3]);
		strcpy(new->user.User_Name,A[4]);;
		new->user.Age = atoi(A[5]);
		new->user.Block_Status = atoi(A[6]);
		new->next = head;
		head = new;
	}
	fclose(fp1);
	FILE *fp2 = fopen("Total_Cash.txt","r");
	fscanf(fp2,"%f",&Total_Cash);
	fclose(fp2);
	return head;
}


void removeAccount(USER_ACCOUNTS *head,char acc[]){  //removes the particular Acc from linked list and updates in the files
	USER_ACCOUNTS *temp,*trav = head,*trav2 = head;
	if(strcmp(trav->user.Acc_No,acc)==0){
		head = trav->next;
		printf("Removed %s Successfully\n",trav->user.User_Name);
		trav2 = head;
		FILE *fp2 = fopen("new_account.txt","a+");
		fprintf(fp2,"%s,%d\n",trav->user.Acc_No,trav->user.OTP);
		fclose(fp2);
		free(trav);
	}
	else{
		while(trav){
			if(strcmp(trav->user.Acc_No,acc)==0){
				temp->next = trav->next;
				printf("Removed %s Successfully\n",trav->user.User_Name);
				FILE *fp2 = fopen("new_account.txt","a+");
				fprintf(fp2,"%s,%d\n",trav->user.Acc_No,trav->user.OTP);
				fclose(fp2);
				free(trav);
				break;
			}
			temp = trav;
			trav = trav->next;
		}}
	FILE *fp1 = fopen("user_details.txt","w");
	while(trav2){
		fprintf(fp1,"%s,%d,%d,%.2f,%s,%d,%d\n",trav2->user.Acc_No,trav2->user.Pin,trav2->user.OTP,trav2->user.Balance,trav2->user.User_Name,trav2->user.Age,trav2->user.Block_Status);
		trav2 = trav2->next;
	}
	fclose(fp1);

}

void changeBlockStatus(USER_ACCOUNTS *head, char acc[]){ //changes the block status the particular account 
	USER_ACCOUNTS *temp,*trav = head,*trav2 = head;
	while(trav){
		if(strcmp(trav->user.Acc_No,acc)==0){
			if(trav->user.Block_Status==1){trav->user.Block_Status = 0;}else{trav->user.Block_Status = 1;}
			printf("Block Status Of User Changed Successfully\n");
			break;
		}
		//temp = trav;
		trav = trav->next;
	}
	FILE *fp1 = fopen("user_details.txt","w");
	while(trav2){
		fprintf(fp1,"%s,%d,%d,%.2f,%s,%d,%d\n",trav2->user.Acc_No,trav2->user.Pin,trav2->user.OTP,trav2->user.Balance,trav2->user.User_Name,trav2->user.Age,trav2->user.Block_Status);
		trav2 = trav2->next;
	}
	fclose(fp1);

}


void ATMTranslog()  //opens the file corresponding to the particular date and prints the tranaction log 
{
	time_t t=time(NULL);
	struct tm tm=*localtime(&t);
	char Date[15],str[500];
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
	FILE *fp1;
	fp1=fopen(Date,"r");
	if(fp1!=NULL)
	{
		while( fgets(str,500,fp1)!=NULL)
		{
			printf("%s\n",str);
		}
		fclose(fp1);
	}
	else
	{
		printf("No Transactions\n");
	}

}

void printAccountDetails(USER_ACCOUNTS *head){ //traverses through the linked list and print the details
	while(head){
		printf("%-30s %s\n","NAME :",head->user.User_Name);
		printf("%-30s %d\n","AGE :",head->user.Age);
		printf("%-30s %.2f\n","AVAILABLE BALANCE :",head->user.Balance);
		printf("%-30s %s\n","ACCOUNT NUMBER :",head->user.Acc_No);

		printf("*****************\n");
		head = head->next;
	}
}		
