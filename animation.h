#define MAX_FRAMES 16
#ifndef __ANIMATION_H
#define __ANIMATION_H
typedef struct Animation {
    Texture2D texture;
    Rectangle frames[MAX_FRAMES];
    float durations[MAX_FRAMES];
} Animation;

Rectangle GetFrameRect(Animation a, float time);
float TotalDuration(Animation a);
#endif
