#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32; // BPP = bits per pixel

const int FRAMES_PER_SECOND = 60;

enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_LEVEL1,
    STATE_LEVEL2,
    STATE_LEVEL3,
    STATE_LEVEL4,
    STATE_EXIT,
};

#endif
