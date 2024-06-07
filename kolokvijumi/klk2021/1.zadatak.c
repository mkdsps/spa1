#include <stdio.h>
#include <stdlib.h>

char ucitajBroj(int *broj){
   char c;
   
   while((c = getchar()) >='0' && c <='9')
      *broj = (*broj * 10) + (c-'0');
   return c;
}

int faktorijal(int x){
   if(x == 1) return 1;
   return x*faktorijal(x-1);
}

int stepen(int a, int b){
   if(b == 0) return 1;
   return a * stepen(a, b-1);
}

int main(){
   char c;
   c = getchar();
   while(c != '\n'){
      
      if (c>= '0' && c <= '9'){
         int broj = c - '0';
         c = ucitajBroj(&broj);

         if (c == '!'){
            printf("%d", faktorijal(broj));
            c = getchar();
         }
         else if (c == '^'){
            int s = 0;
            c = ucitajBroj(&s);
            printf("%d", stepen(broj, s));
         }
         else
            printf("%d", broj);
      }   
      else{
         putchar(c);
         c = getchar();
      }

   }
}
