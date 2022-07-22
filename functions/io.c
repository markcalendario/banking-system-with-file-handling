void Get_PIN(char string[], char SELECTED_PIN[]) {

   // A customized input function to avoid users inserting non-numeric characters
   // Prints askterisk (*) in input stream

   int x = 0;
   
   Start:;

   // Print the string title of the input stream.
   // Example: string[] contains "Enter a PIN number: "
   // By the use of printf below, it will print what string[] contains
   printf("%s", string);
   
   #pragma region 
   // Show number of stars based on the number of index
   // The index tells the program how many characters that the user already entered in the stream.
   // So, if the user enter three chars the x will be 3 also
   // Then it will print three asterisks
   
   // Visualization:
   // User Input: 135
   // Index x: 3
   // The for loop below will print: ***
   for (int i = 0; i < x; i++)
   {
      // Print stars
      printf("*");
   }
   #pragma endregion
   
   // Maintain input stream open if the current index is less than to PIN length.
   // The terminal will continuously ask user to input a character until index (x)...
   // ...reaches the MAX_PIN_LENGTH

   while (x < MAX_PIN_LENGTH) 
   {
      char ch = getch(); // Input stream

      // Check if user entered numeric keys
      if (ch >= '0' && ch <= '9')
      {
         // Store key to PIN (array) using the current index
         SELECTED_PIN[x] = ch;
         // Increment the index
         x++;
      } 
      
      // If user preses backspace key
      else if (ch == 8) 
      { 
         // This condition prevents moving the index into negative
         if (x > 0) x--;
         // Reset the current index of PIN to default. 
         SELECTED_PIN[x] = '\0';
      }
      
      system("cls");
      goto Start;  
   }
}

void Get_User_Account_Number(char string[], char SELECTED_ACC_NUMBER[]) {

   // Description: 
   // A customized input stream to prevent users from inserting non-numeric characters
   int x = 0;

   Start:;
   // Print the guide (Ex. Enter your account number)
   printf("%s", string);
   // Print the current value of the SELECTED_ACC_NUMBER passed by the user
   printf("%s", SELECTED_ACC_NUMBER);

   // Maintain input stream (getch) open...
   // ...until the index x reaches the MAX_ACCOUNT_NUMBER_LENGTH
   while (x < MAX_ACCOUNT_NUMBER_LENGTH)
   {
      char ch = getch();
      // Valid Inputs
      if (ch >= '0' && ch <= '9') 
      {
         SELECTED_ACC_NUMBER[x] = ch;
         x++;
      } 
      
      else if (ch == 8) // Backspace
      {
         // If user preses backspace key
         if (x > 0) x--; // This condition prevents moving the index into  negative
         
         SELECTED_ACC_NUMBER[x] = '\0'; // Reset character of current index to default
      }

      system("cls");
      goto Start;
   }
}

double Get_Double_Input(char *TO_PARSE) {
   double PARSED_DOUBLE;
   char *Garbage;
   PARSED_DOUBLE = strtod(TO_PARSE, &Garbage);

   // If user invalid input the strtod will return 0.00

   // Catch strtod error
   // Reset the Credit back to default.
   // And go back to InsertAmountRegion
   if (PARSED_DOUBLE == 0.0) 
   {
      memset(TO_PARSE, 0, sizeof(TO_PARSE));
      Indicator(FRED, BRED, TO_PARSE, "The amount must contain numbers only.");
      Pause("Press any key to continue.");
      return 0.0;
   }
   for (int i = 0; i < sizeof(Garbage)/ sizeof(Garbage[0]); i++)
   {
      if (Garbage[0] != '\0')
      {
         memset(TO_PARSE, 0, sizeof(TO_PARSE));
         Indicator(FRED, BRED, TO_PARSE, "The amount must contain numbers only.");
         Pause("Press any key to continue.");
         return 0.0;
      }
   }

   return PARSED_DOUBLE;
}