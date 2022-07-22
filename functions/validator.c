int Is_Acc_Number_Registered(char ACC_NUMBER[]) {
   
   FILE *file;
   file = fopen(ACCOUNT_DATABASE_FILE, "rb");
   
   int Acc_Number_Buffer;
   while (fread(&Acc_Number_Buffer, sizeof(int), 1, file) == 1)
   {
      if (Acc_Number_Buffer == atoi(ACC_NUMBER))
      {
         fclose(file);
         return 1;
      }
   }
   
   fclose(file);
   return 0;
}

int Verify_PIN(char PIN_CODE[], char ACCOUNT_NUMBER[]) {

   struct UserData GUD;

   FILE *file;
   file = fopen(BANK_DATABASE_FILE, "r");
   while (fscanf(file,BANK_DATABASE_STRING_FORMAT, &GUD.Acc_Number, GUD.Name, &GUD.PIN, &GUD.Credit, &GUD.Debit, &GUD.Balance) != EOF) {

      if (GUD.PIN == atoi(PIN_CODE) && GUD.Acc_Number == atoi(ACCOUNT_NUMBER))
      {
         fclose(file);
         return 1;
      }
      
   }

   fclose(file);
   return 0;
}