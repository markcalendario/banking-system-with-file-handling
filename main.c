#include "./headers.h"
#include "./functions/validator.c"
#include "./functions/io.c"
#include "./functions/ui.c"
#include "./functions/menu.c"

// Initialization Of Database
// FILE *file = fopen(BANK_DATABASE_FILE, "w");
// fprintf(file, BANK_DATABASE_STRING_FORMAT, 12345, "Sarah", 1997, 25000.00, 1000.00, 24000.00);
// fprintf(file, BANK_DATABASE_STRING_FORMAT, 24689,	"Jacob",	2022,	25000.00, 500.00,	24500.00	);
// fprintf(file, BANK_DATABASE_STRING_FORMAT, 12376, "Beka", 2011, 25000.00, 5000.00, 20000.00);
// fclose(file);

// FILE *file2 = fopen(ACCOUNT_DATABASE_FILE, "wb");
// int a = 12345;
// int b = 24689;
// int c = 12376;
// fwrite(&a, sizeof(a), 1, file2);
// fwrite(&b, sizeof(b), 1, file2);
// fwrite(&c, sizeof(c), 1, file2);
// fclose(file2);

int main() {
   
   char Acc_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char PIN[MAX_PIN_LENGTH + 1] = "\0";
   int TRIES = 0;

   system("cls");
   Display_Welcome();

   // ===============================
   // Account Number
   // ===============================
   AccountNumberInputRegion:;

   // Get the user account number.
   // Go to this function to see the definition.
   Get_User_Account_Number("Enter your 5-digit account number: ", Acc_Number);

   if (!Is_Acc_Number_Registered(Acc_Number))
   {
      system("cls");
      // If the account number that user entered
      // Then show an indicator that this account number does not exists.
      Indicator(FRED, BRED, Acc_Number, "Account number does not exists!");
      // Reset the Acc_Number back to default.
      // It prevents outputing a gibberish values.
      memset(Acc_Number, 0, sizeof(Acc_Number));
      // Pause the screen to make it presentable,
      Pause("Press any key to try again.");
      // Then clear screen
      system("cls");
      // Go back to Account number insert
      goto AccountNumberInputRegion;
   }

   // If account number exists...
   system("cls");
   Indicator(FGREEN, BGREEN, Acc_Number, "Account number is registered.");

   // ===============================
   // PIN Code
   // ===============================
   PINInputRegion:;
   
   // Check if user tried inserting PIN thrice
   if (TRIES == 3)
      // If yes, secure the system. 
      Secure_System(); // Simulates system shutdown

   // Get the User PIN number
   // Go to this function to see the definition.
   Get_PIN("Enter your PIN: ", PIN);

   // Check if PIN of the account number is incorrect   
   if (!Verify_PIN(PIN, Acc_Number))
   {
      // Increment TRIES variable
      TRIES++;
      // Clear screen
      system("cls");
      // Show an indicator in order for user to know that... 
      // they have entered a wrong PIN code for an account number.
      Indicator(FRED, BRED, "X", "Incorrect PIN code!");
      // Print number of attemps left.
      printf("You have %d attempt(s) left.\n", (3 - TRIES));
      
      Pause("Press any key to try again.");
      system("cls");
      // Go back to pin input region.
      goto PINInputRegion;
   }

   // If user entered a correct PIN...
   printf("\n");
   Indicator(FGREEN, BGREEN, Acc_Number, "Success! You are now logged in.");
   Pause("Press any key to operate the system.");
   system("cls");
   
   // ===============================
   // Logged In Region
   // ===============================
   MenuStartRegion:;

   char option;
   // Display a menu
   Display_Menu_Option();
   // Get user option, without echoing to simulate key press experience
   option = getch();
   
   if (option == 'A' || option == 'a')
   {
      // Add New Account
      Add_New_Account();
      system("cls");
   }

   goto MenuStartRegion;
   
}

