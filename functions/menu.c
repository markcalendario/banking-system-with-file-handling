void Display_Menu_Option() {
   Indicator(FBLUE, BBLUE, "Menu", "Press a key to select an option. ");
   Indicator(FGREEN, BGREEN, "A", "Add New Account                     ");
   Indicator(FGREEN, BGREEN, "E", "Edit Account                        ");
   Indicator(FGREEN, BGREEN, "V", "View Account                        ");
   Indicator(FMAGENTA, BMAGENTA, "D", "Delete Account                      ");
   Indicator(FRED, BRED, "Q", "Sign Out                            ");
   Indicator(FRED, BRED, "X", "Exit                                ");
}

void Add_New_Account() {

   char New_Acc_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char New_PIN[MAX_PIN_LENGTH + 1] = "\0";
   char Confirm_New_PIN[MAX_PIN_LENGTH + 1] = "\0";
   char New_Name[256] = "\0";
   double Credit = 0.0;

   // ========================================
   // Get New Account Number
   // ========================================
   NewAccNumberRegion:;
   system("cls");

   // Display all the required input field
   Display_User_Data_Input_Fields(FBLUE, BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name, New_PIN, Credit, 0.0, Credit);
   printf("\n");
   Get_User_Account_Number("Enter new 5-digit account number: ", New_Acc_Number);
   
   // Check if the new account number is registered
   if (Is_Acc_Number_Registered(New_Acc_Number)) {
      printf("\n");
      Indicator(FRED, BRED, New_Acc_Number, "The account number already exists.");
      memset(New_Acc_Number, 0, sizeof(New_Acc_Number));
      Pause("Enter any key to continue.");
      goto NewAccNumberRegion;
   }

   system("cls");

   // Display the updated required field
   Display_User_Data_Input_Fields(FBLUE, BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name, New_PIN, Credit, 0.0, Credit);
   Indicator(FGREEN, BGREEN, New_Acc_Number, "New Account Number Set. Press any key to continue.");
   getch();

   // ========================================
   // Get New Name
   // ========================================
   NewNameInput:;

   system("cls");
   Display_User_Data_Input_Fields(FBLUE,BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name, New_PIN, Credit, 0.0, Credit);

   // Get user name
   printf("\nEnter new name: ");
   scanf("\n%s", New_Name);
   fflush(stdin);
   system("cls");

   // ========================================
   // Get New PIN
   // ========================================
   ConfirmPIN:;

   Display_User_Data_Input_Fields(FBLUE, BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name, New_PIN, Credit, 0.0, Credit);
   printf("\n");
   Get_PIN("Enter new 4-digit PIN: ", New_PIN);
   
   system("cls");
   Display_User_Data_Input_Fields(FBLUE, BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name,  "", Credit, 0.0, Credit);
   printf("\n");
   
   // ========================================
   // Confirm New PIN
   // ========================================

   Get_PIN("Confirm new PIN: ", Confirm_New_PIN);

   if (atoi(New_PIN) != atoi(Confirm_New_PIN))
   {
      printf("\n");
      memset(New_PIN, 0, sizeof(New_PIN));
      memset(Confirm_New_PIN, 0, sizeof(Confirm_New_PIN));
      Indicator(FRED, BRED, "PIN Mismatch", "The PIN confirmation does not match.");
      Pause("Press any key to enter new PIN.");
      system("cls");
      goto ConfirmPIN;
   }

   // ========================================
   // Get New Credit
   // ========================================

   InsertCredit:;

   system("cls");
   Display_User_Data_Input_Fields(FBLUE, BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name, New_PIN, Credit, 0.0, Credit);

   // Get credit amount
   printf("\nEnter credit amount: ");
   int Result = scanf("%lf", &Credit);
   fflush(stdin); 

   // Verify credit amount
   if (Result == 0)
   {
      Indicator(FRED, BRED, "Invalid Input", "The amount that you have inputted is invalid.");
      Pause("Press any key to continue.");
      goto InsertCredit;
   }

   if (Credit < 1)
   {
      Indicator(FRED, BRED, "Invalid Input", "We only accept 1 peso or higher.");
      Pause("Press any key to continue.");
      goto InsertCredit;
   }
   
   // ========================================
   // Storing New Account To Database
   // ========================================

   // Store new data in BANK.TXT
   FILE *Bank_File;
   Bank_File = fopen(BANK_DATABASE_FILE, "a");
   fprintf(Bank_File, BANK_DATABASE_STRING_FORMAT, atoi(New_Acc_Number), New_Name, atoi(New_PIN), Credit, 0.00, Credit);
   fclose(Bank_File);

   system("cls");
   Display_User_Data_Input_Fields(FBLUE, BBLUE, "Add New Account", "Please fill out all required fields.", atoi(New_Acc_Number), New_Name, New_PIN, Credit, 0.0, Credit);
   Indicator(FGREEN, BGREEN, "Success", "This account registered successfully.");
   Pause("Press any key to continue.");
}

int Is_User_Want_Sign_Out() {
   // Signs out a user
   Start:;
   system("cls");
   char x;
   Indicator(FRED, BRED, "Log Out", "You are about to sign out.");
   Indicator(FRED, BRED, "Y", "Yes, sign me out.");
   Indicator(FGREEN, BGREEN, "C", "Cancel");

   x = getch();

   if (x == 'Y' || x == 'y')
      return 1;
   else if (x == 'C' || x == 'c')
      return 0;
   else 
      goto Start;
}

void Edit_Account() {
   char Account_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char PIN[MAX_PIN_LENGTH + 1] = "\0";
   char choice;

   // ========================================
   // Get Account Number To Edit
   // ========================================
   AccountNumberRegion:;
   system("cls");

   memset(Account_Number, 0, sizeof(Account_Number));
   Indicator(FGREEN, BGREEN, "Edit Account Number", "Please fill out the following.");
   Get_User_Account_Number("Enter the account number you want to edit: ", Account_Number);

   // Is Admin

   if (Is_Account_Admin(atoi(Account_Number)))
   {
      system("cls");
      Indicator(FYELLOW, BYELLOW, "Warning", "You cannot edit an admin account.");
      Pause("Press any key to go back to main menu.");
      goto End;
   }

   // Verify account number
   if (!Is_Acc_Number_Registered(Account_Number))
   {
      system("cls");
      Indicator(FRED, BRED, Account_Number, "Record not found!");
      Pause("Press any key to continue.");
      goto AccountNumberRegion;
   }
   
   // ========================================
   // Get User PIN
   // ========================================
   int attempts = 3;
   GetPinRegion:;
   system("cls");

   if (attempts == 0) // Simulate system shutdown
      Secure_System();
   
   Indicator(FGREEN, BGREEN, Account_Number, "You are about to edit this account.");
   Get_PIN("Enter PIN number for this account: ", PIN);

   // Verify PIN
   if (!Verify_PIN(PIN, Account_Number))
   {
      system("cls");
      attempts--;
      Indicator(FRED, BRED, Account_Number, "Incorrect PIN code!");
      printf("You have %d attempt(s) left.\n", attempts);
      Pause("Press any key to continue.");
      goto GetPinRegion;
   }

   // ========================================
   // Depositing Section 
   // ========================================
   DepositRegion:;

   system("cls");
   Display_User_Data(atoi(Account_Number));
   printf("\n");
   Indicator(FCYAN, BCYAN, "Y/N", "Do you want to deposit?");
   choice = getch();
   
   // Check if user want to deposit 
   if (choice == 'Y' || choice == 'y')
   {
      Deposit(atoi(Account_Number));
   } else if (choice == 'N' || choice == 'n') {
      system("cls");
      goto WithdrawRegion;
   } else {
      system("cls");
      Indicator(FRED, BRED, "Invalid Input", "Press [Y]es or [N]o only.");
      Pause("Press any key to try again.");
      goto DepositRegion;
   }

   // ========================================
   // Withdrawal Section 
   // ========================================
   WithdrawRegion:;
   system("cls");
   Display_User_Data(atoi(Account_Number));
   printf("\n");
   Indicator(FCYAN, BCYAN, "Y/N", "Do you want to withdraw?");
   choice = getch();  
   
   // Check if user want to withdraw
   if (choice == 'Y' || choice == 'y')
   {
      Withdraw(atoi(Account_Number));  
   } else if (choice == 'N' || choice == 'n') {
      // No function
   } else {
      system("cls");
      Indicator(FRED, BRED, "Invalid Input", "Press [Y]es or [N]o only.");
      Pause("Press any key to try again.");
      goto WithdrawRegion;
   }

   End:;
}

void Withdraw(int ACCOUNT_NUMBER) {

   // Withdraws money from database

   Start:;
   double Withdraw_Amount;
   system("cls");
   Indicator(FGREEN, BGREEN, "Withdraw", "You are about to withdraw your money."); 
   
   // Get amount of money that users want to withdraw
   printf("Enter amount of money do you want to withdraw: ");
   int Result = scanf("%lf", &Withdraw_Amount);
   fflush(stdin);

   // Check if valid input
   if (Result == 0)
   {
      Indicator(FRED, BRED, "Invalid Input", "The amount that you input is invalid.");
      Pause("Press any key to continue");
      goto Start;
   }

   // Check if negative input
   if (Withdraw_Amount < 0.000000000001)
   {
      Indicator(FRED, BRED, "Invalid Input", "Withdrawing zero or negative amount is not valid.");
      Pause("Press any key to continue");
      goto Start;
   }
   
   // Reflect in database
   FILE *file = fopen(BANK_DATABASE_FILE, "r"); // original database
   FILE *filetemp = fopen(BANK_DATABASE_TEMP_FILE, "w"); // temporary database
   
   struct UserData UserData;
  
   // Read each line of original database
   // And update user account
   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF)
   {
      if (ACCOUNT_NUMBER == UserData.Acc_Number)
      {

         // Check if user has enough money
         if (UserData.Balance < Withdraw_Amount)
         {
            Indicator(FRED, BRED, "!", "Insufficient Amount."); 
            fclose(file);
            fclose(filetemp);
            remove(BANK_DATABASE_TEMP_FILE);
            Pause("Press any key to continue.");
            goto Start;
         } 
         // Allow withdrawal
         else {
            Indicator(FGREEN, BGREEN, "Success", "You have successfully withdrawn your money.");
            printf("%sPrevious Balance: %.2lf%s\n", FYELLOW, UserData.Balance, FWHITE);
            UserData.Balance -= Withdraw_Amount;
            printf("%sNew Balance: %.2lf%s\n", FGREEN, UserData.Balance, FWHITE);
            UserData.Debit += Withdraw_Amount;
         }
      }
      
      // FPRINTF all lines into temporary database
      fprintf(filetemp, BANK_DATABASE_STRING_FORMAT, UserData.Acc_Number, UserData.Name, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);
   }
   
   fclose(file);
   fclose(filetemp);

   // remove the original database
   remove(BANK_DATABASE_FILE);
   // and replace by the temporary database (a new and updated database) 
   rename(BANK_DATABASE_TEMP_FILE, BANK_DATABASE_FILE);

   Pause("Press any key to continue.\n");
   system("cls");
   
   Display_User_Data(ACCOUNT_NUMBER);
   Pause("Press any key to continue.");
   
}

void Deposit(int ACCOUNT_NUMBER) {   
   
   // Deposits money from a user account
   double Deposit_Amount;
   
   // Get amount to deposit
   StartDepositInput:;
   system("cls");
   Indicator(FGREEN, BGREEN, "Deposit", "You are about to deposit money."); 
   printf("Enter amount to deposit: ");
   int Result = scanf("%lf", &Deposit_Amount);
   fflush(stdin);

   // verify amount if valid
   if (Result == 0)
   {
      Indicator(FRED, BRED, "Invalid Amount", "The amount that you input is invalid.");
      Pause("Press any key to continue.");
      goto StartDepositInput;
   }
   
   // verify amount if greater than 1 peso
   if (Deposit_Amount < 1)
   {
      Indicator(FRED, BRED, "Invalid Amount", "We only accept 1 peso or higher.");
      Pause("Press any key to continue.");
      goto StartDepositInput;
   }
   
   struct UserData temp;

   // update the database

   FILE *filetmp = fopen(BANK_DATABASE_TEMP_FILE, "w"); // original database
   FILE *file = fopen(BANK_DATABASE_FILE, "r"); // temporary database

   // read each line and write into temprary database
   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &temp.Acc_Number, temp.Name, &temp.PIN, &temp.Credit, &temp.Debit, &temp.Balance) != EOF)
   {
      // if the scanning process is at the line of user, update the balance and credit
      if (ACCOUNT_NUMBER == temp.Acc_Number)
      {
         Indicator(FGREEN, BGREEN, "Success", "You have successfully deposited your money.");
         printf("%sYour previous balance: %.2lf%s\n", FYELLOW, temp.Balance, FWHITE);
         temp.Balance += Deposit_Amount;
         temp.Credit += Deposit_Amount;
         printf("%sYour new balance: %.2lf%s\n", FGREEN, temp.Balance, FWHITE);
      }

      // write into temporary database (updated database)
      fprintf(filetmp, BANK_DATABASE_STRING_FORMAT, temp.Acc_Number, temp.Name, temp.PIN, temp.Credit, temp.Debit, temp.Balance);
   }

   fclose(filetmp);
   fclose(file);

   // remove the old database and replace by the updated database (temp)
   remove(BANK_DATABASE_FILE);
   rename(BANK_DATABASE_TEMP_FILE, BANK_DATABASE_FILE);
   Pause("Press any key to continue.");
}

void Display_User_Data(int ACCOUNT_NUMBER) {
   
   // Displays individual user data
   
   FILE *file;
   file = fopen(BANK_DATABASE_FILE, "r");

   struct UserData UserData;

   while (1)
   {
      if (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) == EOF)
      {
         Indicator(FRED, BRED, "System Error", "We cannot find your data from our database.");
         Pause("Pressing a key will terminate the system. Try again later.");
         exit(EXIT_FAILURE);
      }
      
      if (ACCOUNT_NUMBER == UserData.Acc_Number) { break; }
   }
   fclose(file);
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "User Data", 
      "Your account information.", 
      ACCOUNT_NUMBER,
      UserData.Name,
      "****",
      UserData.Credit,   
      UserData.Debit,   
      UserData.Balance   
   );
}

void Delete_Account() {
   
   // Deletes account from bank.txt and account.dat
   
   char Account_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char PIN[MAX_PIN_LENGTH + 1] = "\0";

   // Get account number to delete
   AccountNumberRegion:;
   system ("cls");
   Indicator(FRED, BRED, "Account Deletion", "You are about to delete an acount.");
   Get_User_Account_Number("Enter the account number you want to delete: ", Account_Number);

   // Check if account a user account and not an admin

   if (Is_Account_Admin(atoi(Account_Number)))
   {
      printf("\n");
      memset(Account_Number, 0, sizeof(Account_Number));
      Indicator(FYELLOW, BYELLOW, "Warning", "You cannot delete an admin account!");
      Pause("Press any key to go back to main menu.");
      goto End;
   }

   // Verify if that account number exists
   if (!Is_Acc_Number_Registered(Account_Number))
   {
      printf("\n");
      memset(Account_Number, 0, sizeof(Account_Number));
      Indicator(FRED, BRED, Account_Number, "Record not found!");
      Pause("Press any key to continue.");
      goto AccountNumberRegion;
   }

   int attempts = 3;
   PINRegion:;
   system("cls");

   // Shutdown system if user tried to login thrice
   if (attempts == 0)
   {
      Secure_System();
   }
   
   system("cls");
   // Get a user pin for that account
   Get_PIN("Enter PIN code: ", PIN);

   // Verify if PIN is valid
   if (!Verify_PIN(PIN, Account_Number))
   {
      attempts--;
      printf("\n");
      Indicator(FRED, BRED, Account_Number, "Incorrect PIN!");
      printf("You only have %d attempt(s) left.\n", attempts);
      Pause("Press any key to continue.");
      goto PINRegion;
   }
   

   // Show prompt
   PromptRegion:;
   system("cls");
   Display_User_Data(atoi(Account_Number));
   Indicator(FYELLOW, BYELLOW, Account_Number, "Are you sure to delete this account? The data of this account cannot be recovered after this.");
   Indicator(FRED, BRED, "Y", "Yes, I want to delete.");
   Indicator(FGREEN, BGREEN, "N", "No, I have changed my mind.");

   char option = getch();

   if (option == 'Y' || option == 'y')
   {
      Delete_User_Account(atoi(Account_Number));
   } 
   else if (option == 'N' || option == 'n')
   {
      system("cls");
      Pause("Account deletion aborted. Press any key to go back to main menu.");
   } else {
      system("cls");
      Indicator(FRED, BRED, "Invalid Input", "Please enter (Y) Yes or (N) No only.");   
      Pause("Press any key to continue.");   
      goto PromptRegion;
   }
   
   End:;
}

void Delete_User_Account(int ACCOUNT_NUMBER) {
   system("cls");
   
   // Delete user's record from bank.txt

   FILE *file = fopen(BANK_DATABASE_FILE, "r"); // original database
   FILE *filetemp = fopen(BANK_DATABASE_TEMP_FILE, "w"); // new database
   
   struct UserData UserData;

   // scan each line of original database
   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF)
   {
      // If the line is not the account number that we are going to delete,
      // store in the new database
      if (ACCOUNT_NUMBER != UserData.Acc_Number)
      {
         fprintf(filetemp, BANK_DATABASE_STRING_FORMAT, UserData.Acc_Number, UserData.Name, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);
      }
      
   }

   fclose(file);
   fclose(filetemp);

   // replace the old database by the new database
   remove(BANK_DATABASE_FILE);
   rename(BANK_DATABASE_TEMP_FILE, BANK_DATABASE_FILE);

}

void View_Accounts() {
   // Displays all account information
   system("cls");
   FILE *file = fopen(BANK_DATABASE_FILE, "r");

   struct UserData UserData;

   Indicator(FBLUE, BBLUE, "View User Information", "Showing all information...");
   printf("=================================================================================================================\n");
   printf("%s%-10s %-20s %-10s %-15s %-15s %-15s%s\n", FGREEN, "Account", "Name", "PIN", "Credit", "Debit", "Balance", FWHITE);
   printf("=================================================================================================================\n");
   
   // read each line until EOF
   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF)
   {
      if (Is_Account_Admin(UserData.Acc_Number))
      {
         printf("%-10d %s%-20s%s %-10d %-15.2lf %-15.2lf %-15.2lf\n", UserData.Acc_Number, FYELLOW, UserData.Name, FWHITE, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);   
      } else {
         printf("%-10d %s%-20s%s %-10d %-15.2lf %-15.2lf %-15.2lf\n", UserData.Acc_Number, FBLUE, UserData.Name, FWHITE, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);   
      }
      printf("=================================================================================================================\n");
      
   }
   printf("Nothing follows.\n");
   fclose(file);
   Pause("Press any key to continue.");
}