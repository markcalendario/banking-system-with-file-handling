void Database_Check() {
   FILE *File_Bank_Read = fopen(BANK_DATABASE_FILE, "r");

   if (File_Bank_Read == NULL)
   {
      Indicator(FYELLOW, BYELLOW, "Missing Database", "User accounts do exist. Creating database...");
      FILE *file = fopen(BANK_DATABASE_FILE, "w");
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 10001, "Admin", 1111, 0.00, 0.00, 0.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 12345, "Sarah", 1997, 25000.00, 10000.00, 24000.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 24689, "Jacob", 2022, 25000.00, 5000.00, 24500.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 12376, "Beka", 2011, 25000.00, 5000.00, 20000.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 44444, "Kim", 1011, 10000.00, 5000.00, 5000.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 16114, "Sassa", 2335, 10040.30, 5000.00, 5040.30);
      fclose(file);
      Indicator(FGREEN, BGREEN, "Complete", "Bank database initialization complete.");
      Pause("Press any key to check account database.");
   }
   
   FILE *File_Account_Read = fopen(ACCOUNT_DATABASE_FILE, "rb");

   if (File_Account_Read == NULL)
   {
      system("cls");
      Indicator(FYELLOW, BYELLOW, "Missing Database", "Admin accounts do not exist. Creating a default one...");
      FILE *file = fopen(ACCOUNT_DATABASE_FILE, "wb");
      int a = 10001;
      fwrite(&a, sizeof(a), 1, file);
      fclose(file);
      Indicator(FGREEN, BGREEN, "Complete", "Account database initialization complete.");
      Pause("Press any key to continue.");
   }

   fclose(File_Bank_Read);
   fclose(File_Account_Read);
}