#include <stdio.h>
#include "raylib.h"

#include "animation.h"

Rectangle GetFrameRect(Animation a, float time) {
    float totTime = 0.0;
    int f = 0;
    while (f < sizeof(a.durations) / sizeof(float) 
            && a.durations[f] + totTime < time) {
        totTime += a.durations[f];
        f++;
    }
    return a.frames[f];
}

float TotalDuration(Animation a) {
    float tot = 0.0;
    for(int i = 0; i < sizeof(a.durations) / sizeof(float); i++) {
        tot += a.durations[i];
    }
    return tot;
}
