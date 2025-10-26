#ifndef BRICK_GAME_H
#define BRICK_GAME_H

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  START_STATE = 0,
  SPAWN_STATE,
  MOVING_STATE,
  REACH_STATE,
  GAMEOVER_STATE,
  EXIT_STATE,
  FREEZE_STATE,
  WIN_STATE
} GameState_t;

enum { Empty = 0, Body, Food, WIDTH = 10, HEIGHT = 20, GameOver = -1 };
enum { SNAKE, TETRIS, EXIT };

#endif  // BRICK_GAME_H