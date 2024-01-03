#include <windows.h>
#include <stdio.h>
#include <math.h>

double pure[] = {(double)1/1, (double)16/15, (double)9/8, (double)6/5, (double)5/4, (double)4/3, (double)45/32, (double)3/2, (double)8/5, (double)5/3, (double)16/9, (double)15/8, (double)2/1};

void  main( )
{
    int arr[] = {3, 5, 7, 8, 10, 12, 14, 15};
    for (int i = 0; i < 8; i++) {
        Beep(440 * pow(2, arr[i] / 12.0), 300);
    }
    for (int i = 0; i < 8; i++) {
        Beep(440 * pow(2, 3 / 12.0) * pure[arr[i] - 3], 300);
    }
}
