#include "backend.h"

void initGame(TetrisGame_t* game) {
  game->field = (int**)calloc(HEIGHT, sizeof(int*));
  for (int i = 0; i < HEIGHT; i++) {
    game->field[i] = (int*)calloc(WIDTH, sizeof(int));
  }

  game->next = (int**)calloc(SAMPLE_SIZE, sizeof(int*));
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    game->next[i] = (int*)calloc(SAMPLE_SIZE, sizeof(int));
  }
  game->speed = 1;
  game->level = 1;
  game->move_delay = 15;
  game->state = START_STATE;
  loadHighScore(game);
  initPatterns(game);
}

void initFrontInfo(GameInfo_t* fgame) {
  fgame->field = (int**)calloc(HEIGHT, sizeof(int*));
  for (int i = 0; i < HEIGHT; i++) {
    fgame->field[i] = (int*)calloc(WIDTH, sizeof(int));
  }

  fgame->next = (int**)calloc(SAMPLE_SIZE, sizeof(int*));
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    fgame->next[i] = (int*)calloc(SAMPLE_SIZE, sizeof(int));
  }
}

void initPatterns(TetrisGame_t* game) {
  Pattern_t pattern[SAMPLES_CNT] = PATTERNS_INIT;
  for (int k = 0; k < SAMPLES_CNT; ++k) {
    for (int i = 0; i < SAMPLE_SIZE; ++i) {
      for (int j = 0; j < SAMPLE_SIZE; ++j) {
        game->pattern[k].sample[i][j] = pattern[k].sample[i][j];
      }
    }
  }
}

void freeGame(TetrisGame_t* game) {
  if (game) {
    if (game->field) {
      for (int i = 0; i < HEIGHT; i++) {
        if (game->field[i]) {
          free(game->field[i]);
        }
      }
      free(game->field);
    }
    game->field = NULL;

    if (game->next) {
      for (int i = 0; i < SAMPLE_SIZE; i++) {
        if (game->next[i]) {
          free(game->next[i]);
        }
      }
      free(game->next);
    }
    game->next = NULL;
  }
}

void freeFrontInfo(GameInfo_t* fgame) {
  if (fgame) {
    if (fgame->field) {
      for (int i = 0; i < HEIGHT; i++) {
        if (fgame->field[i]) {
          free(fgame->field[i]);
        }
      }
      free(fgame->field);
    }
    fgame->field = NULL;

    if (fgame->next) {
      for (int i = 0; i < SAMPLE_SIZE; i++) {
        if (fgame->next[i]) {
          free(fgame->next[i]);
        }
      }
      free(fgame->next);
    }
    fgame->next = NULL;
  }
}

void rotateFigure(TetrisGame_t* game, bool hold) {
  if (hold) {
    Figure_t tmp = {0};
    for (int y = 0; y < SAMPLE_SIZE; y++) {
      for (int x = 0; x < SAMPLE_SIZE; x++) {
        tmp.shape[y][x] = game->current_figure.shape[y][x];
      }
    }
    tmp.x = game->current_figure.x;
    tmp.y = game->current_figure.y;

    Figure_t rotated_fig = {0};

    for (int y = 0; y < SAMPLE_SIZE; y++) {
      for (int x = 0; x < SAMPLE_SIZE; x++) {
        rotated_fig.shape[x][3 - y] = game->current_figure.shape[y][x];
      }
    }

    if (checkCollide(game)) {
      for (int y = 0; y < SAMPLE_SIZE; y++) {
        for (int x = 0; x < SAMPLE_SIZE; x++) {
          game->current_figure.shape[y][x] = tmp.shape[y][x];
        }
      }
    } else {
      for (int y = 0; y < SAMPLE_SIZE; y++) {
        for (int x = 0; x < SAMPLE_SIZE; x++) {
          game->current_figure.shape[y][x] = rotated_fig.shape[y][x];
        }
      }
    }

    backFromOutOfBounds(game);
  }
}

void backFromOutOfBounds(TetrisGame_t* game) {
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      if (game->current_figure.shape[y][x]) {
        while (game->current_figure.x + x >= WIDTH) {
          game->current_figure.x--;
        }
        while (game->current_figure.x + x < 0) {
          game->current_figure.x++;
        }
      }
    }
  }
}

void checkFullLines(TetrisGame_t* game) {
  int cnt_full_lines = 0;
  for (int y = 0; y < HEIGHT; y++) {
    bool is_full = TRUE;
    for (int x = 0; x < WIDTH; x++) {
      if (!game->field[y][x]) {
        is_full = FALSE;
      }
      if (is_full && x == WIDTH - 1) {
        cnt_full_lines += 1;
        removeFullLines(game, y);
      }
    }
  }
  givePoints(game, cnt_full_lines);
  levelUp(game);
}

void levelUp(TetrisGame_t* game) {
  int score = game->score;
  while (score / (600 * game->level) >= 1 && game->level < 10) {
    game->level += 1;
    game->speed += 1;
    score -= 600;
  }
}

void givePoints(TetrisGame_t* game, int cnt_full_lines) {
  switch (cnt_full_lines) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
      break;
    default:
      break;
  }
}

void removeFullLines(TetrisGame_t* game, int y) {
  for (int x = 0; x < WIDTH; x++) {
    game->field[y][x] = 0;
  }
  for (int newY = y; newY > 0; newY--) {
    for (int x = 0; x < WIDTH; x++) {
      game->field[newY][x] = game->field[newY - 1][x];
    }
  }
}

void moveDown(TetrisGame_t* game) {
  while (!checkCollide(game)) {
    game->current_figure.y++;
  }
}
void moveLeft(TetrisGame_t* game) {
  int newX = game->current_figure.x - 1;
  bool collide = FALSE;
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      if (game->current_figure.shape[y][x] &&
          (game->current_figure.x + x <= 0 ||
           game->field[game->current_figure.y + y][newX + x]))
        collide = TRUE;
    }
  }
  if (!collide) {
    game->current_figure.x--;
  }
}
void moveRight(TetrisGame_t* game) {
  int newX = game->current_figure.x + 1;
  bool collide = FALSE;
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      if (game->current_figure.shape[y][x] &&
          (game->current_figure.x + x >= WIDTH - 1 ||
           game->field[game->current_figure.y + y][newX + x]))
        collide = TRUE;
    }
  }
  if (!collide) {
    game->current_figure.x++;
  }
}

void placeFigure(TetrisGame_t* game) {
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      if (game->current_figure.shape[y][x]) {
        game->field[game->current_figure.y + y][game->current_figure.x + x] =
            Body;
      }
    }
  }
}

bool checkCollide(TetrisGame_t* game) {
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      if (game->current_figure.shape[y][x] == Body) {
        int mapX = game->current_figure.x + x;
        int mapY = game->current_figure.y + y + 1;
        if (mapY >= HEIGHT || mapY <= 0 || game->field[mapY][mapX]) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

void selectNextFigure(TetrisGame_t* game) {
  int rand_pat = rand() % 7;
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      game->next[y][x] = game->pattern[rand_pat].sample[y][x];
    }
  }
}

void dropFigure(TetrisGame_t* game) {
  for (int y = 0; y < SAMPLE_SIZE; y++) {
    for (int x = 0; x < SAMPLE_SIZE; x++) {
      game->current_figure.shape[y][x] = game->next[y][x];
    }
  }
  game->current_figure.x = WIDTH / 2 - 1;
  game->current_figure.y = 0;
}

void loadHighScore(TetrisGame_t* game) {
  FILE* fp = fopen("highscore.txt", "r");
  if (fp) {
    fscanf(fp, "%d", &game->high_score);
    fclose(fp);
  } else {
    game->high_score = 0;
  }
}

void saveHighScore(TetrisGame_t* game) {
  FILE* fp = fopen("highscore.txt", "w");
  if (fp) {
    fprintf(fp, "%d", game->score);
    fclose(fp);
  }
}

void fsmProcess(UserAction_t sig, TetrisGame_t* game, bool hold) {
  switch (game->state) {
    case START_STATE:
      startProcess(sig, game);
      break;
    case SPAWN_STATE:
      spawnProcess(game);
      break;
    case MOVING_STATE:
      moveProcess(sig, game, hold);
      break;
    case REACH_STATE:
      reachProcess(game);
      break;
    case GAMEOVER_STATE:
      gameOverProcess(game, sig);
      break;
    case FREEZE_STATE:
      pauseProcess(game, sig);
      break;
    default:
      break;
  }
}

TetrisGame_t* getTetrisGame() {
  static TetrisGame_t game = {0};
  static bool isStart = TRUE;
  if (isStart) {
    initGame(&game);
    isStart = FALSE;
  }
  return &game;
}

GameState_t getState() {
  TetrisGame_t* game = getTetrisGame();
  return game->state;
}

void userInput(UserAction_t action, bool hold) {
  TetrisGame_t* game = getTetrisGame();
  if (action == Action) hold = true;
  fsmProcess(action, game, hold);
}

void startProcess(UserAction_t sig, TetrisGame_t* game) {
  switch (sig) {
    case Start:
      game->state = SPAWN_STATE;
      selectNextFigure(game);
      dropFigure(game);
      selectNextFigure(game);
      break;
    case Terminate:
      game->state = EXIT_STATE;
      break;
    default:
      game->state = START_STATE;
      break;
  }
}
void spawnProcess(TetrisGame_t* game) {
  dropFigure(game);
  selectNextFigure(game);
  if (checkCollide(game)) {
    game->state = GAMEOVER_STATE;
  } else {
    game->state = MOVING_STATE;
  }
}

void moveProcess(UserAction_t sig, TetrisGame_t* game, bool hold) {
  switch (sig) {
    case Left:
      moveLeft(game);
      break;
    case Right:
      moveRight(game);
      break;
    case Down:
      moveDown(game);
      break;
    case Action:
      rotateFigure(game, hold);
      break;
    case Pause:
      game->state = FREEZE_STATE;
      break;
    case Terminate:
      game->state = EXIT_STATE;
      break;
    case Start:
    case Up:
    default:
      break;
  }
  if (--(game->move_delay) <= game->speed) {
    game->move_delay = 15;
    if (!checkCollide(game)) {
      game->current_figure.y++;
    } else {
      game->state = REACH_STATE;
    }
  }
}

void reachProcess(TetrisGame_t* game) {
  placeFigure(game);
  checkFullLines(game);
  game->state = SPAWN_STATE;
}

void gameOverProcess(TetrisGame_t* game, UserAction_t sig) {
  if (game->score > game->high_score) {
    saveHighScore(game);
  }
  if (sig == Terminate) {
    game->state = EXIT_STATE;
  }
}

void pauseProcess(TetrisGame_t* game, UserAction_t sig) {
  switch (sig) {
    case Pause:
      game->state = MOVING_STATE;
      break;
    case Terminate:
      game->state = EXIT_STATE;
      break;
    case Start:
    case Right:
    case Left:
    case Up:
    case Down:
    case Action:
    default:
      break;
  }
}

GameInfo_t* getGameInfo() {
  static GameInfo_t fgame = {0};
  static bool isStart = TRUE;
  if (isStart) {
    initFrontInfo(&fgame);
    isStart = FALSE;
  }
  return &fgame;
}

GameInfo_t updateCurrentState() {
  return copyStateToFrontInfo(getTetrisGame(), getGameInfo());
}

GameInfo_t copyStateToFrontInfo(TetrisGame_t* game, GameInfo_t* fgame) {
  copyField(fgame, game);
  fgame->high_score = game->high_score;
  fgame->level = game->level;
  copyNextFigure(fgame, game);
  fgame->pause = game->pause;
  fgame->score = game->score;
  fgame->speed = game->speed;
  for (int y = 0; y < SAMPLE_SIZE; ++y) {
    for (int x = 0; x < SAMPLE_SIZE; ++x) {
      if (game->current_figure.shape[y][x] == Body) {
        fgame->field[game->current_figure.y + y][game->current_figure.x + x] =
            Body;
      }
    }
  }
  return *fgame;
}

void copyField(GameInfo_t* fgame, TetrisGame_t* game) {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      fgame->field[y][x] = game->field[y][x];
    }
  }
}

void copyNextFigure(GameInfo_t* fgame, TetrisGame_t* game) {
  for (int y = 0; y < SAMPLE_SIZE; ++y) {
    for (int x = 0; x < SAMPLE_SIZE; ++x) {
      fgame->next[y][x] = game->next[y][x];
    }
  }
}