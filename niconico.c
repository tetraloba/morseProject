#include <windows.h>
#include <stdio.h>
#include <math.h>

#define HZ 440
#define BPM 120.0

void  main( )
{
    int arr[] = {2, -2, 0, 2, 0, -2};
    double length[] = {2.5, 0.5, 1, 0.5, 1, 1};
    for (int time = 0; time < 3; time++) {
        for (int i = 0; i < 6; i++) {
            Beep(HZ * pow(2, arr[i] / 12.0), 1000 * 60 / BPM * length[i]);
        }
    }
}
