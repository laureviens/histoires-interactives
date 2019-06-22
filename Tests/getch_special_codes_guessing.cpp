//From: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes

//Get the char/int code from _getch(), to see the numbers associated with each key!

#include <stdio.h>
#include <conio.h>

int main ()
{
    int ch;

    while ((ch = _getch()) != 27) /* 27 = Esc key */
    {
        printf("%d", ch);
        if (ch == 0 || ch == 224)
            printf (", %d", _getch ()); 
        printf("\n");
    }

    printf("ESC %d\n", ch);

    return (0);
}
