#include <stdio.h>
#include <conio.h>

int main()
{
   int x, y;

   x = 10;
   y = 10;

   gotoxy(x, y);

   printf("C program to change cursor position.");

   getch();
   return 0;
}

