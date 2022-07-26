void Database_Check() {
   FILE *File_Bank_Read = fopen(BANK_DATABASE_FILE, "r");

   if (File_Bank_Read == NULL)
   {
      Indicator(FYELLOW, BYELLOW, "Missing Database", "User accounts does not exists. Creating data for admins...");
      FILE *file = fopen(BANK_DATABASE_FILE, "w");
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 10001, "Kenneth", 1902, 0.00, 0.00, 0.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 10002, "Kim", 3245, 0.00, 0.00, 0.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 10003, "Nicole", 4444, 0.00, 0.00, 0.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 10004, "Elaine", 9944, 0.00, 0.00, 0.00);
      fprintf(file, BANK_DATABASE_STRING_FORMAT, 10005, "JohnRace", 6677, 0.00, 0.00, 0.00);
      fclose(file);
      Indicator(FGREEN, BGREEN, "Complete", "Bank database initialization complete.");
      Pause("Press any key to check account database.");
   }
   
   FILE *File_Account_Read = fopen(ACCOUNT_DATABASE_FILE, "rb");

   if (File_Account_Read == NULL)
   {
      system("cls");
      Indicator(FYELLOW, BYELLOW, "Missing Database", "Admin accounts does not exists. Creating a default one...");
      FILE *file = fopen(ACCOUNT_DATABASE_FILE, "wb");
      int a = 10001;
      int b = 10002;
      int c = 10003;
      int d = 10004;
      int e = 10005;
      fwrite(&a, sizeof(a), 1, file);
      fwrite(&b, sizeof(b), 1, file);
      fwrite(&c, sizeof(c), 1, file);
      fwrite(&d, sizeof(d), 1, file);
      fwrite(&e, sizeof(e), 1, file);
      fclose(file);
      Indicator(FGREEN, BGREEN, "Complete", "Account database initialization complete.");
      Pause("Press any key to continue.");
   }

   fclose(File_Bank_Read);
   fclose(File_Account_Read);
}