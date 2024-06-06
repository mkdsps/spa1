#include <stdio.h>
#include <stdlib.h>

int daLiJeSlovo(char c){
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z');
}


void okreniRec(char* rec, int n, int i){
   if (i <= n / 2){
      char t = rec[i];
      rec[i] = rec[n - i - 1];
      rec[n - i - 1] = t;
      okreniRec(rec,n, i +1);
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
            okreniRec(rec, n, 0);

         printf("%s", rec);
         free(rec);
      }
      else{
         putchar(c);
         c = getchar();
      }
   }

}
