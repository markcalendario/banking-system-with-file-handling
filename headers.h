#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ===============================
// Environment Variables
// ===============================

#define MAX_PIN_LENGTH 4
#define MAX_ACCOUNT_NUMBER_LENGTH 5
#define BANK_NAME "Banco de Universidad de Filipinas Politecnico"

// ===============================
// Database
// ===============================

#define BANK_DATABASE_FILE "./database/bank.txt"
#define BANK_DATABASE_TEMP_FILE "./database/bank.temp.txt"
#define ACCOUNT_DATABASE_FILE "./database/account.dat"
#define ACCOUNT_DATABASE_TEMP_FILE "./database/account.temp.dat"
#define BANK_DATABASE_STRING_FORMAT "%d : %s : %d : %lf : %lf : %lf\n"
#define ACCOUNT_DATABASE_STRING_FORMAT "%d\n"

// ===============================
// Colors
// ===============================
// Docs: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// ===============================

#define FBLACK     "\x1b[30m"
#define FRED     "\x1b[31m"
#define FGREEN   "\x1b[32m"
#define FYELLOW  "\x1b[33m"
#define FBLUE    "\x1b[34m"
#define FMAGENTA "\x1b[35m"
#define FCYAN    "\x1b[36m"
#define FWHITE   "\x1b[37m"

#define BBLACK     "\x1b[40m"
#define BRED     "\x1b[41m"
#define BGREEN   "\x1b[42m"
#define BYELLOW  "\x1b[43m"
#define BBLUE    "\x1b[44m"
#define BMAGENTA "\x1b[45m"
#define BCYAN    "\x1b[46m"
#define BWHITE   "\x1b[47m"

// ===============================
// Structure
// ===============================

struct UserData {
   int Acc_Number;
   char Name[80];
   int PIN;
   double Credit;
   double Debit;
   double Balance;
};

// ===============================
// Prototypes
// ===============================

// VALIDATOR.C
int Is_Acc_Number_Registered(char *);
int Is_Account_Admin(int);
int Verify_PIN(char *, char *);

// UI.C
void Display_Welcome();
void Indicator(char *, char *, char *, char *);
void Display_Goodbye();
void Pause(char *);
void Secure_System();
void Display_Menu_Option();
void Display_User_Data_Input_Fields(char *, char *, char *, char *, int , char *, char *, double, double, double);

// IO.C
void Get_User_Account_Number(char *, char *);
void Get_PIN(char *, char *);

// MENU.C
void Add_New_Account();
void Edit_Account();
void Deposit(int);
void Withdraw(int);
void Display_User_Data(int);
void Delete_Account();
void Delete_User_Account(int);
void View_Accounts();
int Is_User_Want_Sign_Out();

// DATABASE.C
void Database_Check();


