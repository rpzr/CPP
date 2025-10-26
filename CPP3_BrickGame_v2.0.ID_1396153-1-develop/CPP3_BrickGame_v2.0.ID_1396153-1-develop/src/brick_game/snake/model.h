#ifndef _MODEL_H
#define _MODEL_H

#include <cstdlib>
#include <ctime>
#include <deque>
#include <map>

#include "../common/brickgame.h"

class Model {
  GameState_t currentState_;
  std::pair<int, int> food;
  std::deque<std::pair<int, int>> snakeCoords;
  std::deque<UserAction_t> inputBuffer;
  bool direction_flag = false;
  int** field_;
  int speed_;
  int boosted_speed_;
  int move_timer_;
  int level_;
  int score_;
  int high_score_;
  UserAction_t currentDirection;

  void updateField();
  void generateFood();
  bool checkCollision();
  void moveSnake();
  void resetMoveTimer(int actual_speed);
  void processPlayingState(UserAction_t action);
  void processPausedState(UserAction_t action);
  void processGameOverState(UserAction_t action);

 public:
  Model();
  ~Model();

  void initializeGame();
  void fsmProc(UserAction_t action, bool hold);
  GameInfo_t getGameInfo() const;
  GameState_t getState() const;
  UserAction_t getCurrentDirection() const { return currentDirection; }
};

#endif