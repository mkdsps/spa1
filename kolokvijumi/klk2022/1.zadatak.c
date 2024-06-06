#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char lower(char c){
   return (c >= 'A' && c <= 'Z') ? c-'A'+'a' : c;
}//postoji funk tolower ali zna da ne radi...


int proveri(char* rec, int l, int d){
   if(l >= d) return 1;
   
   if (rec[l] == rec[d])
      return proveri(rec, l+1, d-1);
   return 0;
}


int main(){
   char c;
   c = getchar();

   while(c != '\n'){
      if (lower(c) >= 'a' && lower(c) <= 'z'){
         int linija = 256;
         char* rec = (char*)malloc(linija*sizeof(char));
         int n = 0;

         while(lower(c) >= 'a' && lower(c) <= 'z'){
            if(n >= linija){
               linija+= 256;

               rec = (char*)realloc(rec, linija*sizeof(char));
            }
            
            rec[n++] = lower(c);
            c = getchar(); 
         }
         rec[n] = '\0';

         if(proveri(rec, 0, n-1))
            for (int i = 0 ; i < n ; i++)
               putchar(rec[i]-'a'+'A');
               
         else
            printf("%s", rec);
         free(rec);
      }
      else {
         putchar(c);
         c = getchar();
      }
   }
}
