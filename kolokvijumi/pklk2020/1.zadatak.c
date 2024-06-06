#include <stdio.h>
#include <stdlib.h>

int daLiJeSlovo(char c){
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z');
}


void okreniRec(char* rec, int n){
   if (n > 1){
      char t = rec[0];
      rec[0] = rec[n-1];
      rec[n - 1] = t;
      okreniRec(rec+1, n - 2);
   }
}

int main(){
   char c = getchar();
   
   while(c != '\n'){
      if (daLiJeSlovo(c)){
         int brojac = 0;
         int duzina = 256;
         char *rec = (char*)malloc(duzina* sizeof(char));
         int n = 0;
        
         while(daLiJeSlovo(c)){
            if(c >= 'A' && c <='Z') 
               brojac++;

            if (n > duzina){
               duzina += 256;
               rec = (char *)realloc(rec, duzina * sizeof(char));
            }

            rec[n++] = c;
            c = getchar();
         }
         rec[n] = '\0';
         if (brojac == 1 && rec[n-1]>='A' && rec[n-1] <= 'Z')
            okreniRec(rec, n);

         printf("%s", rec);
         free(rec);
      }
      else{
         putchar(c);
         c = getchar();
      }
   }

}
