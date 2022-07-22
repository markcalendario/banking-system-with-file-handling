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

   // This function adds account information to a bank.txt.
   // In addition, it registers the account number to the binary file account.dat.

   #pragma region VARIABLE_INITIALIZATION
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
   #pragma endregion VARIABLE_INITIALIZATION

   // ==============================================================
   // Get User Account Number Region 
   // ==============================================================
   NewAccNumberRegion:;

   system("cls");
   // Display required input fields.
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "", Parsed_Credit, 0.0, Parsed_Credit);
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
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "", Parsed_Credit, 0.0, Parsed_Credit);
   Indicator(FGREEN, BGREEN, New_Acc_Number, "New Account Number Set. Press any key to continue.");
   getch();

   // ==============================================================
   // New Name Region 
   // ==============================================================
   NewNameInput:;

   system("cls");
   // Display the required fields again.
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "", Parsed_Credit, 0.0, Parsed_Credit);
   // Get user name and store to New_Name
   printf("\nEnter new name: ");
   scanf("\n%s", New_Name);

   system("cls");

   // ==============================================================
   // Get PIN Region 
   // ==============================================================
   ConfirmPIN:;

   // Display the required fields again
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "", Parsed_Credit, 0.0, Parsed_Credit);
   printf("\n");
   // Get user PIN and store to New_PIN
   Get_PIN("Enter new PIN: ", New_PIN);
   
   system("cls");
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "", Parsed_Credit, 0.0, Parsed_Credit);
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
   // Display all required fields, but show PIN as ****
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "****", Parsed_Credit, 0.0, Parsed_Credit);

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

   char *Chars_Credit_Garbage;
   Parsed_Credit = strtod(Credit, &Chars_Credit_Garbage);

   // If user invalid input the strtod will return 0.00
   // Valid Inputs: 123a 1. 1.a
   // Invalid: a123 

   // Catch strtod error
   // Reset the Credit back to default.
   // And go back to InsertCreditRegion
   if (Parsed_Credit == 0.0) 
   {
      memset(Credit, 0, sizeof(Credit));
      Indicator(FRED, BRED, Credit, "Credit amount must contain numbers only.");
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
   Display_User_Data_Input_Fields(atoi(New_Acc_Number), New_Name, "****", Parsed_Credit, 0.0, Parsed_Credit);
   Indicator(FGREEN, BGREEN, "Success", "This account registered successfully.");
   Pause("Press any key to continue.");
}
