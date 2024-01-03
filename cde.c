#include <windows.h>
#include <stdio.h>
#include <math.h>

void  main( )
{
    int arr[] = {3, 5, 7, 8, 10, 12, 14, 15};
    for (int i = 0; i < 8; i++) {
        Beep(440 * pow(2, arr[i] / 12.0), 300);
    }
}
