#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

// Helper Functions

// To print a single Character
int printchar(char c){
   write(1, &c, 1);
   return 1;
}

// To print a string
int printstr(const char *str){
   int count = 0;
   while(*str){
      count += printchar(*str++);
   }
   return count;
}

// To print an Integer
int printint(int n){
   // Integer will get printed by converting it into a string first
   char buffer[12];
   char *ptr = buffer + sizeof(buffer) - 1; // Puts the pointer to second last element of buffer so that \0 or null character can be placed to terminate the string 
   int count = 0;

   *ptr = '\0';
   int is_negative = n < 0;
   if(is_negative){
      n = -n; // This will multiply n with minus making it positive in case if it is negative
   }
   do
   {
      ptr--;
      *ptr = (n%10) + '0'; // (n%10) will get the last digit of n then adding a '0' in it will add ascii of 0 that will make this number into its string ascii
      count++;
      n /= 10;
   } while (n > 0);

   if(is_negative){
      ptr--;
      *ptr = '-';  // Again putting minus sign in front of the number
      count++;
   }

   printstr(ptr); // Printing the string
   return count;
}

// Making own printf function _printf
int _printf(const char *format, ...){
   va_list args;
   va_start(args, format);
   int count = 0;
   const char* p;
   for(p = format; *p !='\0'; p++){
      if(*p == '%'){
         p++;
            switch (*p) {
                case 'd': {
                    int i = va_arg(args, int);
                    count += printint(i);
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char*);
                    count += printstr(s);
                    break;
                }
                case 'c': {
                    int c = va_arg(args, int); // char is promoted to int
                    count += printchar(c);
                    break;
                }
                default:
                    count += printchar('%');
                    count += printchar(*p);
                    break;
            }
      }else{
         count += printchar(*p);
      }
   }

   va_end(args);
   return count;
}


int main(){
   int len = printstr("This function also return number of bytes it printed just like printf function\n");
   _printf("Number of bytes: %d\n", len);
   len = printint(235);
   int len2 = _printf("\nNumber of bytes: %d\n", len);
   _printf("Number of bytes from my _printf function: %d\n", len2);
   return 0;
}