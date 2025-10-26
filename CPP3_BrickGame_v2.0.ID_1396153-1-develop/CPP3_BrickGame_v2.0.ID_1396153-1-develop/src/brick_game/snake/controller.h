#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../common/brickgame.h"
#include "./model.h"

class Controller {
 public:
  explicit Controller(Model &model) : model_(model) {}

  void userInput(UserAction_t action, bool hold) {
    if (action == Action) {
      hold = true;
    }
    model_.fsmProc(action, hold);
  }

  UserAction_t getCurrentDirection() const {
    return model_.getCurrentDirection();
  }

  GameInfo_t updateCurrentState() { return model_.getGameInfo(); }
  GameState_t getGameState() { return model_.getState(); }

 private:
  Model &model_;
};

#endif