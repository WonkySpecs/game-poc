#include <math.h>
#include <stdio.h>
#include "raylib.h"

#include "constants.h"
#include "player.h"

void InitAnimations();

const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 32;

double animationTimer = 0;
double neutralAnimationTimer = 0;
Player player;

void InitPlayer() {
    player.pos = (Vector2) { 400.0, 400.0 };
    player.vel = (Vector2) { 0.0, 0.0 };
    player.rot = 0.0;
    player.state = NEUTRAL;
    InitAnimations();
}

void InitAnimations() {
    Texture2D texture = LoadTexture("assets/shields_up.png");
    int maxSpriteNum =(int)(texture.height / SPRITE_HEIGHT) - 1;

    player.animations[NEUTRAL] = (Animation){
        texture,
        { (Rectangle){0,
                      maxSpriteNum * SPRITE_HEIGHT,
                      SPRITE_WIDTH, SPRITE_HEIGHT},
          (Rectangle){0,
                      maxSpriteNum * SPRITE_HEIGHT - 1,
                      SPRITE_WIDTH, SPRITE_HEIGHT},
        },
        {35.0, 35.0},
    };
    player.animations[NEUTRAL_SHIELDING] = (Animation){
        texture,
    };
    player.animations[SHIELDING] = (Animation){
        texture, { (Rectangle){0, 0, SPRITE_WIDTH, SPRITE_HEIGHT}}, {150.0},
    };
    for (int frameNum = 0; frameNum <= maxSpriteNum; frameNum++) {
        player.animations[NEUTRAL_SHIELDING].frames[frameNum] = (Rectangle) { 
            0,
            (maxSpriteNum - frameNum) * SPRITE_HEIGHT,
            SPRITE_WIDTH,
            SPRITE_HEIGHT, };
        player.animations[NEUTRAL_SHIELDING].durations[frameNum] = 2.0f;
    }
}

void UpdatePlayer(float delta) {
    switch(player.state) {
        case NEUTRAL:
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                player.state = NEUTRAL_SHIELDING;
                neutralAnimationTimer = 0;
            } else {
                neutralAnimationTimer = fmod(neutralAnimationTimer + delta, 70);
            }
            break;
        case NEUTRAL_SHIELDING:
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                animationTimer += delta;
            } else {
                animationTimer -= delta;
            }

            if (animationTimer <= 0) {
                player.state = NEUTRAL;
                animationTimer = 0;
                neutralAnimationTimer = 0;
            } else if(animationTimer >= TotalDuration(player.animations[player.state])) {
                animationTimer = TotalDuration(player.animations[player.state]);
                neutralAnimationTimer = 0;
                player.state = SHIELDING;
            }

            break;
        case SHIELDING:
            if (!IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                player.state = NEUTRAL_SHIELDING;
                neutralAnimationTimer = 0;
            } else {
                neutralAnimationTimer = fmod(neutralAnimationTimer + delta, 70);
            }

            break;
    }
    player.pos.x += player.vel.x;
    player.pos.y += player.vel.y;
    Vector2 facing = (Vector2) { GetMouseX() - player.pos.x, 
                                 GetMouseY() - player.pos.y };
    player.rot = atan2(facing.y, facing.x) * 360 / (2 * 3.14159) + 90;
}

void DrawPlayer() {
    Rectangle dest = (Rectangle) { 
        player.pos.x, player.pos.y, SPRITE_WIDTH * 2, SPRITE_HEIGHT * 2
    };
    float animationTime = player.state == NEUTRAL_SHIELDING ? animationTimer : neutralAnimationTimer;
    DrawTexturePro(player.animations[player.state].texture,
                   GetFrameRect(player.animations[player.state], animationTime),
                   dest, 
                   (Vector2){ SPRITE_WIDTH, SPRITE_HEIGHT },
                   player.rot,
                   WHITE);
}

void UnloadPlayer() {
    for(int a = 0; a < sizeof(player.animations) / sizeof(Animation); a ++) {
        UnloadTexture(player.animations[a].texture);
    }

}
