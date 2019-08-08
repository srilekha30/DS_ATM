                                             ﻿ATM APPLICATION(PROJECT 016)
TEAM MEMBERS:
1. Sanyem Gupta(Roll No.201601082)
2. V.Sai Rathan(Roll No.201601104)
3. N.Srilekha(Roll No.201601055)
4. Sowmya Vasuki J(Roll No.201601035)

	In this project, we have mainly focused on two types of interactions, i.e. User interaction and Admin Interaction. The Program Starts With 2 options – 1. Already A User, Login, 2. Not A User. In the first option there is a special login ID and password for Admin which has a different menu for Admin Interaction.
 Admin Login Id – 0000000000, Admin Password – 0000.
  
	We have used 4 structures in the code, 2 for maintaining linked lists used in the program and 2 for User Details and New User Details respectively. 

->We have included all the structures in a file “structures.c” and included it as a library.
In the main function, we have called two functions. Rest of the things are done from hence.
1. “insertUserDataFromFile” – It is for getting the user data from the file in linked list.
2. “Execution” – This is where the program starts.

->We have in general maintained 4 files for database. 
First File is “user_details.txt”. This file contains the information about all the current users.Each line contains the details(comma as delimiter) in the following order – Account No., Pin, OTP, Account Balance, First Name of the User, Age, Block Status(Bool).

Second File is “Total_Cash.txt”. This file contains only one float number which is the total cash available in the ATM Machine.

Third File is “new_account.txt”. This file contains the information used for creating new accounts. The order in the file is as follows – Account No., OTP.

Fourth File is for Transaction Log. A new file is created on a daily basis with the name as the current date. In this file all the transaction logs are updates of all the users. The order is as follows- Account No., Transaction ID(Daily starts from 1), Current Balance of The User, First Name of the User, Time of the Transaction, Type(Debit or Credit or Failed transaction).

->The Data Structure we have used is Linked List,each node comprising of the user details loaded from the user details file.

InsertUserDataFromFile:
           Parameters Passed- head pointer(USER_ACCOUNTS)
                This function reads the user details from the file ”user_details.txt” and inserts the respective details into the node(USER_DETAILS) and thereby inserts the node into the linked list.The head pointer is returned to the main function.It also initializes the Total_Cash to the value in the file “Total_Cash.txt”.

-----------------------------------------------------------------------------------------------------------------------------------------
Admin Interaction:- All the tasks can be done only if admin logins with his/her id.
The Following are the functions we have used in the order.

1. RemoveAccount:
   Parameters Passed – Head pointer(USER_ACCOUNTS),Acc.no of the account to be removed.
                 In this function we traverse through the linked list till we find the corresonding account no. And then we delete the particular node,add the corresponding Account Details in the “new_account.txt” and update the file “user_details.txt”. 
2. ChangeBlockStatus:
    Parameters Passed – Head pointer(USER_ACCOUNTS),Acc.no of the account to change block status.
               In this function we traverse through the linked list till we find the corresonding account no. And then we change the block status and update the file “user_details.txt”.  
3. ATMTranslog: 
         In this function we check if there exists a file of transaction log
(name of the file is the date) and print the details in the file.
4. PrintAccountDetails:
      Parameters Passed - Head pointer(USER_ACCOUNTS)
           Traversing through the Linked List and printing all the details.
           
5. AdminMenu:
      Parameters Passed - Head pointer(USER_ACCOUNTS)
      It displays all the tasks that the admin can perform in the following order.An integer is taken as input for choosing the task to be performed and then the following tasks are performed for the corresponding integers.
1. Remove An User Account:
         Account No. Is taken and Function 1 is called.
2. Block/Unblock A User:
                    Account No. Is taken and Function 2 is called.    
3. Load Cash Into ATM:
The amount to be loaded is taken as input.It is added to total_cash and updated in “Total_cash.txt”. 
4. ATM Transaction Log:
         Function 3 is called.
5. Display All Account Details:
           Function 4 is called.

------------------------------------------------------------------------------------------------------------------------------------------------

 User Interaction:- All the tasks can be done only if user logins with his/her credentials.

       The Following are the functions we have used in the order.
1.   UpdateInFiles:
             Parameters Passed – Head Pointer(USER_ACCOUNTS).
           This Function updates the file “user_details.txt” with all the changes made in the Linked List.It also updates the file “Total_Cost.txt”.
           
2.   GenerateTransId:   
           Parameters Passed – File name of the Current Day’s transaction log.
                 This Function generates the Transaction Id for each Transaction in the given file. 
                 
3.TransferUserFunds: 
           	Parameters Passed – Current User,Head Pointer(USER_ACCOUNTS).
         	In the function the Beneficiary Account No. Is taken as input.
         	If the particular account is existant the the amount to be transferred is taken as input.if the amount entered is less than the current user’s balance the amount is transfered and this transaction is added to the transaction log file corresponding to the date as a debit transaction to current user and credit transaction to the Beneficiary Account Holder.
Function 1 is called to update the files.
        	If the amount entered is more than the current user’s balance
the transaction is added to the transaction log as a Failed transaction.If the Account No. is not present there is a error message.
4. Usertranslog:
    		Parameters Passed – Current User’s account no.
                In this Function the current date is obtained and the Transaction log file corresponding to the date is opened.We scan through the first 10 characters(Account no.) and compare them with the current users account no.If they match the particular line is printed. If there is no Transaction Log of the particular date or if there is no transaction corresponding to the account no. The message is displayed.
5. Changepin:
            Parameters Passed – CurrentUser(USER_ACCOUNTS),Head Pointer(USER_ACCOUNTS).
            New pin is taken and is updated in the files(Function 1).
6. Viewprofile:
              Parameters Passed – Current User(USER_ACCOUNTS).
              Prints the current user details.
7.Updateprofile: 
                Parameters Passed – CurrentUser(USER_ACCOUNTS),Head Pointer(USER_ACCOUNTS).
                New inputs(Name,Age)are taken and updated in the files(Function 1).
8.UserMenu:
           Parameters Passed – CurrentUser(USER_ACCOUNTS),Head Pointer(USER_ACCOUNTS).            
	    The Tasks that can be performed are in the following order with the respective Op-Codes.
1. Check Account Balance:
Balance is displayed.
2. Deposit Money:
The amount to be deposited is taken as input.It is added to the Total_Cash,User balance,Updated in transaction Log as Credit,and also updated in the Files(Function 1).
3. Withdraw Money:
The amount to be withdrawn is taken as input.If it is less than Transaction Limit,Total_Cash,Balance,it is subtracted from the Total_Cash,User balance,Updated in transaction Log as Debit,and also updated in the Files(Function 1).In other cases the respective message is displayed.
4. Transfer Funds:
Function 3 is called.
5. Display Transaction Log:
Function 4 is called.
6. Change Pin:
Function 5 is called.
7. View Profile:
Function 6 is called.
8. Update Profile:
Function 7 is called.

----------------------------------------------------------------------------------------------------------------------------------------------

USER LOGIN:
        Parameters Passed – Head Pointer(USER_ACCOUNTS).
       Account No. Is taken as input.If it matches with the admin credentials,the function AdminMenu is called.
If it matches with any of the credentials of the nodes in the Linked List it asks for the PIN ,verifies the pin and then UserMenu function is called.
CreateNewAccount:
	Parameters Passed – Head Pointer(USER_ACCOUNTS)
	The Account Details from the file “new_account.txt” are taken,the user is allotted the account number and when he enters the correct OTP ,the details are added to the linked list and then updated in the respective files(Update Files)
Execution:
         If already an user ,USER LOGIN function is called.
	Else CreateNewAccount is called.
