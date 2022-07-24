void Display_Menu_Option() {
   Indicator(FBLUE, BBLUE, "Menu", "Press a key to select an option. ");
   Indicator(FGREEN, BGREEN, "A", "Add New Account                     ");
   Indicator(FGREEN, BGREEN, "E", "Edit Account                        ");
   Indicator(FGREEN, BGREEN, "V", "View Account                        ");
   Indicator(FMAGENTA, BMAGENTA, "D", "Delete Account                      ");
   Indicator(FRED, BRED, "Q", "Sign Out                            ");
   Indicator(FRED, BRED, "X", "Exit                                ");
}

// ==============================================================
// Add New Account
// ==============================================================
void Add_New_Account() {

   // This function adds account information to a bank.txt.
   // In addition, it registers the account number to the binary file account.dat.

   // Variable Initialization
   // The variables New_Acc_Number, New_PIN, Confirm_New_PIN, and Credit
   // Are in the form of array.

   // It is initialized as array for us to be able to use the scanf string
   // To prevent using "%d" as scanf format

   // These variables will be parsed after the user inserted all the required field.
   // Parsers: atoi and strtod
   char New_Acc_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char New_PIN[MAX_PIN_LENGTH + 1] = "\0";
   char Confirm_New_PIN[MAX_PIN_LENGTH + 1] = "\0";
   char New_Name[256] = "\0";
   char Credit[256] ="\0";
   double Parsed_Credit = 0.0;

   // ==============================================================
   // Get User Account Number Region 
   // ==============================================================
   NewAccNumberRegion:;

   system("cls");
   // Display required input fields.
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, New_PIN, 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit);
   printf("\n");
   // Get a user input for a new account number.
   Get_User_Account_Number("Enter new account number: ", New_Acc_Number);
   
   // Check if account number already exists.
   // Show an error indicators.
   // Then, reset the New_Acc_Number function back to default.
   if (Is_Acc_Number_Registered(New_Acc_Number)) {
      printf("\n");
      Indicator(FRED, BRED, New_Acc_Number, "The account number already exists.");
      memset(New_Acc_Number, 0, sizeof(New_Acc_Number));
      Pause("Enter any key to continue.");
      goto NewAccNumberRegion;
   }

   // If the account number is unique...
   // Show a success indicator.
   system("cls");
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, New_PIN, 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit
   );
   Indicator(FGREEN, BGREEN, New_Acc_Number, "New Account Number Set. Press any key to continue.");
   getch();

   // ==============================================================
   // New Name Region 
   // ==============================================================
   NewNameInput:;

   system("cls");
   // Display the required fields again.
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, New_PIN, 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit
   );
   // Get user name and store to New_Name
   printf("\nEnter new name: ");
   scanf("\n%s", New_Name);

   system("cls");

   // ==============================================================
   // Get PIN Region 
   // ==============================================================
   ConfirmPIN:;

   // Display the required fields again
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, New_PIN, 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit
   );
   printf("\n");
   Get_PIN("Enter new PIN: ", New_PIN);
   
   system("cls");
   // Get user PIN and store to New_PIN
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, 
      "", 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit
   );
   printf("\n");
   
   // Confirm new pin by asking user to input again the previously entered pin 
   Get_PIN("Confirm new PIN: ", Confirm_New_PIN);

   // If confirmation does not match
   if (atoi(New_PIN) != atoi(Confirm_New_PIN))
   {
      printf("\n");
      Indicator(FRED, BRED, "PIN Mismatch", "The PIN confirmation does not match.");
      Pause("Press any key to continue.");
      system("cls");
      goto ConfirmPIN;
   }

   // ==============================================================
   // Insert New Credit Region 
   // ==============================================================
   InsertCredit:;

   system("cls");
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, 
      New_PIN, 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit
   );

   printf("\nEnter credit amount: ");
   // Flush the input stream if the user entered name with space 
   fflush(stdin);
   // Get user desired amount for credit
   scanf("\n%s", Credit);

   // This variable Chars_Credit_Garbage serves as a storage for chars in input stream
   // For example, user entered 544100fgh
   // The strtod will parse the string into double
   // The "fgh" will be stored on that variable.
   // However, the 544100 will be stored in Parsed_Credit.
   Parsed_Credit = Get_Double_Input(Credit);
   if (Parsed_Credit == 0.0)
   {
      goto InsertCredit;
   }

   if (Parsed_Credit < 0)
   {
      system("cls");
      Parsed_Credit = 0.00;
      Indicator(FRED, BRED, "Invalid Input", "Credit amount cannot be negative.");
      Pause("Press any key to continue.");
      goto InsertCredit;
   }
   
   
   
   // ==============================================================
   // Inserting Into Bank Text File 
   // ==============================================================
   
   FILE *Bank_File;
   Bank_File = fopen(BANK_DATABASE_FILE, "a");
   fprintf(Bank_File, BANK_DATABASE_STRING_FORMAT, atoi(New_Acc_Number), New_Name, atoi(New_PIN), Parsed_Credit, 0.00, Parsed_Credit);
   fclose(Bank_File);

   // ==============================================================
   // Inserting Into Account Dat File 
   // ==============================================================

   int Parsed_New_Acc_Number = atoi(New_Acc_Number);
   
   FILE *Account_File;
   Account_File = fopen(ACCOUNT_DATABASE_FILE, "ab");
   fwrite(&Parsed_New_Acc_Number, sizeof(Parsed_New_Acc_Number), 1, Account_File);
   fclose(Account_File);

   system("cls");
   Display_User_Data_Input_Fields(
      FBLUE,
      BBLUE,
      "Add New Account",
      "Please fill out all required fields.",
      atoi(New_Acc_Number), 
      New_Name, 
      New_PIN, 
      Parsed_Credit, 
      0.0, 
      Parsed_Credit
   );
   Indicator(FGREEN, BGREEN, "Success", "This account registered successfully.");
   Pause("Press any key to continue.");
}

int Is_User_Want_Sign_Out() {
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

   // Get account number
   AccountNumberRegion:;
   system("cls");

   memset(Account_Number, 0, sizeof(Account_Number));
   Indicator(FGREEN, BGREEN, "Edit Account Number", "Please fill out the following.");
   Get_User_Account_Number("Enter the account number you want to edit: ", Account_Number);
   
   if (!Is_Acc_Number_Registered(Account_Number))
   {
      system("cls");
      Indicator(FRED, BRED, Account_Number, "Record not found!");
      Pause("Press any key to continue.");
      goto AccountNumberRegion;
   }
   
   // Get PIN
   GetPinRegion:;
   system("cls");

   int attempts = 3;

   if (attempts == 0)
      Secure_System();
   
   Indicator(FGREEN, BGREEN, Account_Number, "You are about to edit this account.");
   Get_PIN("Enter PIN number for this account: ", PIN);

   if (!Verify_PIN(PIN, Account_Number))
   {
      system("cls");
      attempts--;
      Indicator(FRED, BRED, Account_Number, "Incorrect PIN code!");
      Pause("Press any key to continue.");
      goto GetPinRegion;
   }

   DepositRegion:;
   system("cls");
   Display_User_Data(atoi(Account_Number));
   printf("\n");
   Indicator(FCYAN, BCYAN, "Y/N", "Do you want to deposit?");
   choice = getch();
   
   if (choice == 'Y' || choice == 'y')
   {
      Deposit(Account_Number);
   } else if (choice == 'N' || choice == 'n') {
      system("cls");
      goto WithdrawRegion;
   } else {
      system("cls");
      Indicator(FRED, BRED, "Invalid Input", "Press [Y]es or [N]o only.");
      Pause("Press any key to try again.");
      goto DepositRegion;
   }

   WithdrawRegion:;
   system("cls");
   Display_User_Data(atoi(Account_Number));
   printf("\n");
   Indicator(FCYAN, BCYAN, "Y/N", "Do you want to withdraw?");
   choice = getch();  
   
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
}

void Withdraw(int ACCOUNT_NUMBER) {

   Start:;
   char AMOUNT[256] = "\0";
   double PARSED_AMOUNT = 0;
   system("cls");
   Indicator(FGREEN, BGREEN, "Withdraw", "You are about to withdraw your money."); 
   
   printf("Enter amount of money do you want to withdraw: ");
   scanf("%s", AMOUNT);
   fflush(stdin);
   PARSED_AMOUNT = Get_Double_Input(AMOUNT);

   if (PARSED_AMOUNT == 0)
   {
      Indicator(FRED, BRED, "Invalid Input", "Please enter a valid amount.");
      Pause("Press any key to continue");
      goto Start;
   }

   // Open File
   FILE *file = fopen(BANK_DATABASE_FILE, "r");
   FILE *filetemp = fopen(BANK_DATABASE_TEMP_FILE, "w");
   
   struct UserData UserData;

  
   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF)
   {
      if (ACCOUNT_NUMBER == UserData.Acc_Number)
      {

         if (UserData.Balance < PARSED_AMOUNT)
         {
            system("cls");
            Indicator(FRED, BRED, "!", "Insufficient Amount."); 
            fclose(file);
            fclose(filetemp);
            remove(BANK_DATABASE_TEMP_FILE);
            Pause("Press any key to continue.");
            goto Start;
         } else {
            printf("%sPrevious Balance: %.2lf%s\n", UserData.Balance, FRED, FWHITE);
            UserData.Balance -= PARSED_AMOUNT;
            printf("%sNew Balance: %.2lf%s\n", UserData.Balance, FRED, FWHITE);
            UserData.Debit += PARSED_AMOUNT;
         }
      }
      
      fprintf(filetemp, BANK_DATABASE_STRING_FORMAT, UserData.Acc_Number, UserData.Name, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);
   }
   
   fclose(file);
   fclose(filetemp);

   remove(BANK_DATABASE_FILE);
   rename(BANK_DATABASE_TEMP_FILE, BANK_DATABASE_FILE);

   Display_User_Data(ACCOUNT_NUMBER);
   Pause("Press any key to continue.");
   
}

void Display_User_Data(int ACCOUNT_NUMBER) {
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
      "You account data.", 
      ACCOUNT_NUMBER,
      UserData.Name,
      "****",
      UserData.Credit,   
      UserData.Debit,   
      UserData.Balance   
   );
}

void Deposit(char *ACCOUNT_NUMBER) {   
   char String_Deposit[256];
   double Deposit_Amount;
   
   StartDepositInput:;
   system("cls");
   Indicator(FGREEN, BGREEN, ACCOUNT_NUMBER, "You are about to deposit your money."); 
   printf("Enter amount to deposit: ");
   scanf("%s", String_Deposit);

   Deposit_Amount = Get_Double_Input(String_Deposit);

   if (Deposit_Amount == 0.0)
   {
      goto StartDepositInput;
   } else if (Deposit_Amount < 0)
   {
      Indicator(FRED, BRED, "Invalid Amount", "Depositing negative amount is not possible.");
      Pause("Press any key to continue.");
      goto StartDepositInput;
   }
   

   struct UserData temp;

   FILE *filetmp = fopen(BANK_DATABASE_TEMP_FILE, "w");
   FILE *file = fopen(BANK_DATABASE_FILE, "r");

   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &temp.Acc_Number, temp.Name, &temp.PIN, &temp.Credit, &temp.Debit, &temp.Balance) != EOF)
   {
      if (atoi(ACCOUNT_NUMBER) == temp.Acc_Number)
      {
         Indicator(FGREEN, BGREEN, "Success", "Your account has been updated successfully.");
         printf("%sYour previous balance: %.2lf%s\n", FRED, temp.Balance, FWHITE);
         temp.Balance += Deposit_Amount;
         temp.Credit += Deposit_Amount;
         printf("%sYour new balance: %.2lf%s\n", FGREEN, temp.Balance, FWHITE);
      }
      fprintf(filetmp, BANK_DATABASE_STRING_FORMAT, temp.Acc_Number, temp.Name, temp.PIN, temp.Credit, temp.Debit, temp.Balance);
   }

   fclose(filetmp);
   fclose(file);

   remove(BANK_DATABASE_FILE);
   rename(BANK_DATABASE_TEMP_FILE, BANK_DATABASE_FILE);
   Pause("Press any key to continue.");
}

void Delete_Account() {
   char Account_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char PIN[MAX_PIN_LENGTH + 1] = "\0";

   AccountNumberRegion:;
   system ("cls");
   Indicator(FRED, BRED, "Account Deletion", "You are about to delete an acount.");
   Get_User_Account_Number("Enter the account number you want to delete: ", Account_Number);

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

   if (attempts == 0)
   {
      printf("\nYou only have %d attempt(s) left.", attempts);
      Secure_System();
   }
   
   system("cls");
   Get_PIN("Enter PIN code: ", PIN);

   if (!Verify_PIN(PIN, Account_Number))
   {
      attempts--;
      printf("\n");
      Indicator(FRED, BRED, Account_Number, "Incorrect PIN!");
      Pause("Press any key to continue.");
      goto PINRegion;
   }

   Indicator(FBLUE, BBLUE, Account_Number, "Your account information.");
   Display_User_Data(atoi(Account_Number));
   Pause("Press any key to continue.");

   PromptRegion:;
   system("cls");
   Indicator(FBLUE, BBLUE, Account_Number, "Are you sure to delete this account?");
   Indicator(FRED, BRED, "Y", "Yes, I want to delete.");
   Indicator(FGREEN, BGREEN, "N", "No, I have changed my mind.");

   char option = getch();

   if (option == 'Y' || option == 'y')
   {
      Delete_User_Account(atoi(Account_Number));
   } 
   else if (option != 'N' || option != 'n')
   {
      Indicator(FRED, BRED, "Invalid Input", "Please enter (Y) Yes or (N) No only.");      
      goto PromptRegion;
   }

}

void Delete_User_Account(int ACCOUNT_NUMBER) {
   
   // Delete in BANK.TXT
   FILE *file = fopen(BANK_DATABASE_FILE, "r");
   FILE *filetemp = fopen(BANK_DATABASE_TEMP_FILE, "w");
   
   struct UserData UserData;

   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF)
   {
      if (ACCOUNT_NUMBER != UserData.Acc_Number)
      {
         fprintf(filetemp, BANK_DATABASE_STRING_FORMAT, UserData.Acc_Number, UserData.Name, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);
      }
      
   }

   fclose(file);
   fclose(filetemp);

   remove(BANK_DATABASE_FILE);
   rename(BANK_DATABASE_TEMP_FILE, BANK_DATABASE_FILE);

   // Delete ACCOUNT.DAT

   FILE *filedat = fopen(ACCOUNT_DATABASE_FILE, "rb");
   FILE *filedattemp = fopen(ACCOUNT_DATABASE_TEMP_FILE, "wb");

   int Account_Number_Buffer;

   while (fread(&Account_Number_Buffer, sizeof(Account_Number_Buffer), 1, file) == 1)
   {
      if (Account_Number_Buffer != ACCOUNT_NUMBER)
      {
         fwrite(&Account_Number_Buffer, sizeof(Account_Number_Buffer), 1, filedattemp);
      }
   }
   
   fclose(filedat);
   fclose(filedattemp);

   remove(ACCOUNT_DATABASE_FILE);
   rename(ACCOUNT_DATABASE_TEMP_FILE, ACCOUNT_DATABASE_FILE);
   
   Indicator(FGREEN, BGREEN, "Success", "Account deleted successfully.");
   Pause("Press any key to continue.");

}

void View_Accounts() {

   system("cls");
   FILE *file = fopen(BANK_DATABASE_FILE, "r");

   struct UserData UserData;

   Indicator(FBLUE, BBLUE, "View User Information", "Showing all information...");
   printf("=================================================================================================================\n");
   printf("%sAccount Number\t|\tAccount Name\t|\tPIN\t|\tCredit\t\t|\tDebit\t|\tBalance%s\n", FGREEN,FWHITE);

   while (fscanf(file, BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF)
   {
      printf("%d\t\t|\t%s\t\t|\t%d\t|\t%.2lf\t|\t%.2lf\t|\t%.2lf\n", UserData.Acc_Number, UserData.Name, UserData.PIN, UserData.Credit, UserData.Debit, UserData.Balance);   
   }

   fclose(file);
   printf("=================================================================================================================\n");
   Pause("Press any key to continue.");
}