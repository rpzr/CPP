#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/common/brickgame.h"

#ifdef __cplusplus
extern "C" {
#endif

void initCurses(void);
void destroyCurses(void);
void drawGameField(const GameInfo_t* game);
void drawInfoPanel(const GameInfo_t* game, GameState_t state, int game_type);
void renderGameScreen(const GameInfo_t* game, GameState_t state, int game_type);
UserAction_t convertKeyToAction(int key);
UserAction_t processInput(void);
int showMainMenu();

#ifdef __cplusplus
}
#endif

#endif  // FRONTEND_H