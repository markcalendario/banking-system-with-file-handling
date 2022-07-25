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

double Parse_To_Double(char *TO_PARSE) {

   // A customized input that parses a string to a valid double value.
   // Returns 0 if invalid, otherwise the parsed value.

   // Example of valid inputs: 12.22, -11.12, 5
   // Example of invalid inputs: a12.3, 43.0a 

   // If characters found in a string, return 0

   double PARSED_DOUBLE;
   char *Garbage;
   // Parse using strtod
   PARSED_DOUBLE = strtod(TO_PARSE, &Garbage);

   // Check if invalid
   if (PARSED_DOUBLE == 0.0) 
   {
      memset(TO_PARSE, 0, sizeof(TO_PARSE));
      Indicator(FRED, BRED, "Invalid Input", "The amount that you have inputted is not valid.");
      Pause("Press any key to continue.");
      return 0.0;
   }

   // Check if there's a character in a string.
   for (int i = 0; i < sizeof(Garbage)/ sizeof(Garbage[0]); i++)
   {
      if (Garbage[0] != '\0') // If character caught, return 0.
      {
         memset(TO_PARSE, 0, sizeof(TO_PARSE));
         Indicator(FRED, BRED, TO_PARSE, "The amount must contain numbers only.");
         Pause("Press any key to continue.");
         return 0.0;
      }
   }

   return PARSED_DOUBLE;
}