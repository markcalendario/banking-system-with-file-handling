void Indicator(char foreground[], char background[], char indicate[], char string[]) {
   printf("%s %s %s%s %s %s%s\n", background, indicate, BWHITE, foreground, string, FWHITE, BBLACK);
}

void Display_User_Data_Input_Fields(char *FCOLOR, char *BCOLOR, char *TITLE, char *TEXT, int ACCOUNT_NUMBER, char *NAME, char *PIN, double CREDIT, double DEBIT, double BALANCE) {
   Indicator(FCOLOR, BCOLOR, TITLE, TEXT);
   printf("%sAccount Number:%s %d\n", FCOLOR, FWHITE, ACCOUNT_NUMBER);
   printf("%sAccount Name:%s %s\n", FCOLOR, FWHITE, NAME);
   printf("%sAccount PIN:%s %s\n", FCOLOR, FWHITE, PIN);
   printf("%sNew Credit:%s %.2lf\n", FCOLOR, FWHITE, CREDIT);
   printf("%sAccount Balance:%s %.2lf\n", FCOLOR, FWHITE, BALANCE);
   printf("%sAccount Debit:%s %.2lf\n", FCOLOR, FWHITE, DEBIT);
}

void Display_Welcome() {
   char Greet_Str[50] = "Welcome to ";
   strcat(Greet_Str, BANK_NAME);
   Indicator(FBLUE, BBLUE, "", Greet_Str);
   Pause("Press any key to start.");
   system("cls");
}

void Pause(char str[]) {
   printf("%s", str);
   getch();
}

void Secure_System() {
   system("cls");
   Indicator(FYELLOW, BYELLOW, "!", "For security reasons, the system is temporarily locked.");
   Pause("The bank staff is coming to assist you. Thank you.");
   exit(EXIT_FAILURE);
}

void Display_Goodbye() {
   system("cls");
   Indicator(FBLUE, BBLUE, "", "Thank you for using our services.");
   Pause("Press any key to close.");
   exit(EXIT_SUCCESS);
}