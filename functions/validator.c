int Is_Account_Admin(int ACC_NUMBER) {
   
   // Checks if account number is admin
   // Returns: 0, 1

   FILE *file;
   file = fopen(ACCOUNT_DATABASE_FILE, "rb");
   
   int Acc_Number_Buffer;
   while (fread(&Acc_Number_Buffer, sizeof(int), 1, file) == 1)
   {
      if (Acc_Number_Buffer == ACC_NUMBER)
      {
         fclose(file);
         return 1;
      }
   }
   
   fclose(file);
   return 0;
}

int Is_Acc_Number_Registered(char ACC_NUMBER[]) {
   
   // Checks if a PIN of a specific account number is valid
   // Returns: 0, 1

   struct UserData UserData;

   FILE *file;
   file = fopen(BANK_DATABASE_FILE, "r");
   while (fscanf(file,BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF) {

      if (UserData.Acc_Number == atoi(ACC_NUMBER))
      {
         fclose(file);
         return 1;
      }
   }
   fclose(file);
   return 0;
}

int Verify_PIN(char PIN_CODE[], char ACCOUNT_NUMBER[]) {

   // Checks if a PIN of a specific account number is valid
   // Returns: 0, 1

   struct UserData UserData;

   FILE *file;
   file = fopen(BANK_DATABASE_FILE, "r");
   while (fscanf(file,BANK_DATABASE_STRING_FORMAT, &UserData.Acc_Number, UserData.Name, &UserData.PIN, &UserData.Credit, &UserData.Debit, &UserData.Balance) != EOF) {

      if (UserData.PIN == atoi(PIN_CODE) && UserData.Acc_Number == atoi(ACCOUNT_NUMBER))
      {
         fclose(file);
         return 1;
      }
   }
   fclose(file);
   return 0;
}