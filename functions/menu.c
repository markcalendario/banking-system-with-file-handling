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

   char String_Deposit[256];
   float Parsed_Deposit;
   char String_Withdraw[256];
   float Parsed_Withdraw;

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
   Indicator(FBLUE, BBLUE, "Y/N", "Do you want to deposit?");
   choice = getch();
   
   if (choice == 'Y' || choice == 'y')
   {
      Deposit(Account_Number);
   } else if (choice != 'N' || choice != 'n') {
      system("cls");
      Indicator(FRED, BRED, "Invalid Input", "Press [Y]es or [N]o only.");
      Pause("Press any key to try again.");
      goto DepositRegion;
   }

   WithdrawRegion:;
   Display_User_Data(atoi(Account_Number));
   Pause("Press any key to continue.");
   system("cls");
   Indicator(FGREEN, BGREEN, "Y/N", "Do you want to withdraw?");
   choice = getch();  

   if (choice == 'Y' || choice == 'y')
   {
      // Deposit(Account_Number); TODO  
   } else if (choice != 'N' || choice != 'n') {
      system("cls");
      Indicator(FRED, BRED, "Invalid Input", "Press [Y]es or [N]o only.");
      Pause("Press any key to try again.");
      goto WithdrawRegion;
   }
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
         Indicator(FGREEN, BBLUE, "Success", "Your account has been updated successfully.");
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
}