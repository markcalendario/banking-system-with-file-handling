void Get_PIN(char string[], char SELECTED_PIN[]) {

   // A customized user input stream preventing users inputting characters in a stream.
   // It also prevents users from typing more than four (4) numbers.

   int x = 0;
   
   Start:;
   printf("%s", string);
   
   // Print a star instead of chars/numbers.
   #pragma region PRINT STARS
   for (int i = 0; i < x; i++)
   {
      printf("*");
   }
   #pragma endregion

   // Get user input using getch
   while (x < MAX_PIN_LENGTH) 
   {
      char ch = getch();

      // Register user input in a parameter if user inputs 0-9
      if (ch >= '0' && ch <= '9')
      {
         SELECTED_PIN[x] = ch;
         x++;
      } 
      
      // If user pressed backspace (ASCII CODE OF BACKSPACE: 8),
      // Remove a previously registered number to a pin parameter 
      else if (ch == 8) 
      { 
         if (x > 0) x--; // Prevent user from going to a negative index
         SELECTED_PIN[x] = '\0';
      }
      
      system("cls");
      goto Start;  
   }
}

void Get_User_Account_Number(char string[], char SELECTED_ACC_NUMBER[]) {

   // A customized user input stream preventing users inputting characters in a stream.
   // It also prevents users from typing more than five (5) numbers.

   int x = 0;

   Start:;
   printf("%s", string); // Print a text: "Enter PIN" (may vary according to the passed guide string) 
   printf("%s", SELECTED_ACC_NUMBER); // Print the account number beside the guide string

   while (x < MAX_ACCOUNT_NUMBER_LENGTH)
   {
      char ch = getch();

      // Register 0 - 9 only
      if (ch >= '0' && ch <= '9')
      {
         SELECTED_ACC_NUMBER[x] = ch;
         x++;
      } 
      
      // If user presses a backspace
      else if (ch == 8) 
      {
         if (x > 0) x--; // Prevent negative index
         SELECTED_ACC_NUMBER[x] = '\0'; // Reset index
      }

      system("cls");
      goto Start;
   }
}