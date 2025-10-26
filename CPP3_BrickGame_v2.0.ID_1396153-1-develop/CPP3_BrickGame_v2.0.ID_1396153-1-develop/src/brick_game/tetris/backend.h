#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../common/brickgame.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE 0
#define SAMPLES_CNT 7
#define SAMPLE_SIZE 4
#define PATTERNS_INIT                                             \
  {                                                               \
      {{{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}}, \
      {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}, \
      {{{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}}, \
      {{{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}}}, \
      {{{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}, \
      {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}}, \
      {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}}}, \
  };

typedef struct pattern {
  char sample[SAMPLE_SIZE][SAMPLE_SIZE];
} Pattern_t;

typedef struct figure {
  int x;
  int y;
  char shape[SAMPLE_SIZE][SAMPLE_SIZE];
} Figure_t;

typedef struct {
  int **field;
  int **next;
  Figure_t current_figure;
  Pattern_t pattern[SAMPLES_CNT];
  GameState_t state;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int move_delay;
} TetrisGame_t;

void initGame(TetrisGame_t *game);
void initFrontInfo(GameInfo_t *fgame);
void initPatterns(TetrisGame_t *game);
void freeGame(TetrisGame_t *game);
void freeFrontInfo(GameInfo_t *fgame);
void rotateFigure(TetrisGame_t *game, bool hold);
void checkFullLines(TetrisGame_t *game);
void removeFullLines(TetrisGame_t *game, int y);
void placeFigure(TetrisGame_t *game);
bool checkCollide(TetrisGame_t *game);
void selectNextFigure(TetrisGame_t *game);
void dropFigure(TetrisGame_t *game);
void givePoints(TetrisGame_t *game, int cnt_full_lines);
void levelUp(TetrisGame_t *game);
void loadHighScore(TetrisGame_t *game);
void saveHighScore(TetrisGame_t *game);

void userInput(UserAction_t action, bool hold);

void fsmProcess(UserAction_t sig, TetrisGame_t *game, bool hold);
void startProcess(UserAction_t sig, TetrisGame_t *game);
void spawnProcess(TetrisGame_t *game);
void moveProcess(UserAction_t sig, TetrisGame_t *game, bool hold);
void reachProcess(TetrisGame_t *game);
void gameOverProcess(TetrisGame_t *game, UserAction_t sig);
void pauseProcess(TetrisGame_t *game, UserAction_t sig);
void moveDown(TetrisGame_t *game);
void moveLeft(TetrisGame_t *game);
void moveRight(TetrisGame_t *game);
void backFromOutOfBounds(TetrisGame_t *game);
void copyField(GameInfo_t *fgame, TetrisGame_t *game);
void copyNextFigure(GameInfo_t *fgame, TetrisGame_t *game);
GameInfo_t updateCurrentState();
GameInfo_t copyStateToFrontInfo(TetrisGame_t *game, GameInfo_t *fgame);
GameInfo_t *getGameInfo();
TetrisGame_t *getTetrisGame();
GameState_t getState();
#ifdef __cplusplus
}
#endif

#endif