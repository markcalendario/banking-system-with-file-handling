/*
*
*  BANK SYSTEM
*  BSCS 1-1
*  COMPUTER PROGRAMMING 2
*  FINAL PROJECT
*  POLYTECHNIC UNIVERSITY OF THE PHILIPPINES
*
*  THIS PROGRAM WAS DESIGNED, PROGRAMMED, AND CREATED BY THE FOLLOWING STUDENTS:
*  - ROMALAINE ANNE BELLO
*  - MARK KENNETH CALENDARIO
*  - JOHN RACE LEVARDO
*  - NICOLE MARCELLANA
*  - KIM MONTANA
*
*/

#include "./headers.h"
#include "./functions/validator.c"
#include "./functions/io.c"
#include "./functions/ui.c"
#include "./functions/menu.c"
#include "./functions/database.c"

int main() {
   system("cls");
   // ==============================================
      Database_Check();
   // ==============================================

   char Acc_Number[MAX_ACCOUNT_NUMBER_LENGTH + 1] = "\0";
   char PIN[MAX_PIN_LENGTH + 1] = "\0";
   int TRIES = 0;

   StartRegion:;
   system("cls");
   Display_Welcome();

   AccountNumberInputRegion:;
   // ==============================================
   // Login Portal
   // ==============================================
   Indicator(FBLUE, BBLUE, "Admin Login", "Please login your account.");

   // Get user account number.
   Get_User_Account_Number("Enter your 5-digit account number: ", Acc_Number);
   
   // Check if account registered. 
   if (!Is_Account_Admin(atoi(Acc_Number)))
   {
      system("cls");
      Indicator(FRED, BRED, Acc_Number, "Account number is not admin or not registered!");
      memset(Acc_Number, 0, sizeof(Acc_Number));
      Pause("Press any key to try again.");
      system("cls");
      goto AccountNumberInputRegion;
   }

   system("cls");
   Indicator(FGREEN, BGREEN, Acc_Number, "You are about to login as an admin.");

   PINInputRegion:;
   if (TRIES == 3) { Secure_System(); } // Stop the system if user tried to login thrice.

   // Get user PIN.
   Get_PIN("Enter your PIN: ", PIN);

   // Verify a PIN.
   if (!Verify_PIN(PIN, Acc_Number))
   {
      TRIES++;
      system("cls");
      Indicator(FRED, BRED, "X", "Incorrect PIN code!");
      printf("You have %d attempt(s) left.\n", (3 - TRIES));   
      Pause("Press any key to try again.");
      system("cls");
      goto PINInputRegion;
   }

   system("cls");
   Indicator(FGREEN, BGREEN, Acc_Number, "Success! You are now logged in.");
   Pause("Press any key to operate the system.");
   system("cls");
   
   // ==============================================
   // Main Menu
   // ==============================================
   MenuStartRegion:;

   char option;
   Display_Menu_Option();
   option = getch();

   switch (option)
   {
   case 'A':
   case 'a':
      Add_New_Account();
      system("cls");
      break;
   case 'E':
   case 'e':
      Edit_Account();
      system("cls");
      break;
   case 'D':
   case 'd':
      Delete_Account();
      system("cls");
      break;
   case 'V':
   case 'v':
      View_Accounts();
      system("cls");
      break;
   case 'Q':
   case 'q':
      if (Is_User_Want_Sign_Out()) {
         memset(Acc_Number, 0, sizeof(Acc_Number));
         system("cls");
         goto StartRegion;
      }
      else {
         system("cls");
         goto MenuStartRegion;
      }
      break;
   case 'X':
   case 'x':
      Display_Goodbye();
      break;
   }
   
   system("cls");
   goto MenuStartRegion;  
}

