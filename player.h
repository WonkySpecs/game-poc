#include "animation.h"

#ifndef __PLAYER_H
#define __PLAYER_H
typedef enum { NEUTRAL, NEUTRAL_SHIELDING, SHIELDING } State;
typedef struct Player {
    Vector2 pos;
    Vector2 vel;
    float rot;
    Animation animations[3];
    State state;
} Player;

void InitPlayer();
void UpdatePlayer(float delta);
void DrawPlayer();
void UnloadPlayer();
#endif
