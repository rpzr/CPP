#include "../gui/cli/frontend.h"
#include "./common/brickgame.h"
#include "./snake/controller.h"
#include "./snake/model.h"
#include "./tetris/backend.h"

void runSnake() {
  Model model;
  Controller controller(model);
  bool isPlaying = true;
  while (isPlaying) {
    UserAction_t act = processInput();
    controller.userInput(act, false);
    GameState_t state = controller.getGameState();
    GameInfo_t info = controller.updateCurrentState();
    if (state == EXIT_STATE) isPlaying = false;
    renderGameScreen(&info, state, SNAKE);
  }
}

void runTetris() {
  TetrisGame_t* game = getTetrisGame();
  GameInfo_t* fgame = getGameInfo();

  bool isPlaying = true;
  while (isPlaying) {
    UserAction_t act = processInput();
    userInput(act, false);
    *fgame = updateCurrentState();
    GameState_t state = getState();
    if (state == EXIT_STATE) isPlaying = false;
    renderGameScreen(fgame, state, TETRIS);
  }

  freeFrontInfo(fgame);
  freeGame(game);
}

int main() {
  srand(time(NULL));
  initCurses();

  int selected;
  bool gameIsFinished = false;
  do {
    selected = showMainMenu();
    switch (selected) {
      case SNAKE:
        runSnake();
        gameIsFinished = true;
        break;
      case TETRIS:
        runTetris();
        gameIsFinished = true;
        break;
      case EXIT:
        break;
    }
  } while (selected != EXIT && !gameIsFinished);

  destroyCurses();
  return 0;
}