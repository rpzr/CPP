#include "frontend.h"

static WINDOW *main_win, *game_win, *info_win, *buffer;

void initCurses(void) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(50);
  start_color();

  init_pair(1, COLOR_BLUE, COLOR_BLUE);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);

  main_win = newwin(LINES, COLS, 0, 0);
  buffer = newwin(LINES, COLS, 0, 0);

  game_win = derwin(buffer, HEIGHT + 2, WIDTH * 2 + 2, 1, 1);
  info_win = derwin(buffer, HEIGHT + 2, WIDTH * 2, 1, WIDTH * 2 + 4);

  keypad(buffer, TRUE);
  nodelay(buffer, TRUE);
}

void destroyCurses(void) {
  delwin(game_win);
  delwin(info_win);
  delwin(buffer);
  delwin(main_win);
  endwin();
}

void drawGameField(const GameInfo_t* game) {
  werase(game_win);
  box(game_win, 0, 0);

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (game->field[y][x] == Body) {
        wattron(game_win, COLOR_PAIR(1));
        mvwaddch(game_win, y + 1, x * 2 + 1, ' ');
        mvwaddch(game_win, y + 1, x * 2 + 2, ' ');
        wattroff(game_win, COLOR_PAIR(1));
      }

      if (game->field[y][x] == Food) {
        wattron(game_win, COLOR_PAIR(2));
        mvwaddch(game_win, y + 1, x * 2 + 1, ' ');
        mvwaddch(game_win, y + 1, x * 2 + 2, ' ');
        wattroff(game_win, COLOR_PAIR(2));
      }
    }
  }
}

void drawInfoPanel(const GameInfo_t* game, GameState_t state, int game_type) {
  werase(info_win);
  box(info_win, 0, 0);

  mvwprintw(info_win, 1, 1, "Score: %d", game->score);
  mvwprintw(info_win, 2, 1, "High Score: %d", game->high_score);
  mvwprintw(info_win, 3, 1, "Level: %d", game->level);
  mvwprintw(info_win, 4, 1, "Speed: %d", game->speed);

  if (game_type == TETRIS) {
    mvwprintw(info_win, 6, 1, "Next figure:");
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        if (game->next[y][x]) {
          wattron(info_win, COLOR_PAIR(1));
          mvwaddch(info_win, 8 + y, 7 + x * 2, ' ');
          mvwaddch(info_win, 8 + y, 8 + x * 2, ' ');
          wattroff(info_win, COLOR_PAIR(1));
        }
      }
    }
  }
  const char* state_msg = "";
  switch (state) {
    case START_STATE:
      state_msg = "Press ENT to start";
      break;
    case GAMEOVER_STATE:
      state_msg = "GAME OVER";
      break;
    case FREEZE_STATE:
      state_msg = "PAUSED";
      break;
    default:
      break;
  }
  mvwprintw(info_win, HEIGHT - 2, 1, "%s", state_msg);
}

void renderGameScreen(const GameInfo_t* game, GameState_t state,
                      int game_type) {
  werase(buffer);
  drawGameField(game);
  drawInfoPanel(game, state, game_type);

  wnoutrefresh(buffer);
  doupdate();
}

UserAction_t convertKeyToAction(int key) {
  UserAction_t act = (UserAction_t)-1;
  switch (key) {
    case KEY_UP:
      act = Up;
      break;
    case KEY_DOWN:
      act = Down;
      break;
    case KEY_LEFT:
      act = Left;
      break;
    case KEY_RIGHT:
      act = Right;
      break;
    case 'p':
      act = Pause;
      break;
    case ' ':
      act = Action;
      break;
    case 10:
      act = Start;
      break;
    case 27:
      act = Terminate;
      break;
  }
  return act;
}

UserAction_t processInput(void) { return convertKeyToAction(getch()); }

int showMainMenu() {
  clear();
  printw("Choose game: \n\n");
  printw("1. SNAKE\n");
  printw("2. TETRIS\n");
  printw("3. EXIT\n");
  refresh();

  int choice = getch();
  int game_type = -1;
  switch (choice) {
    case '1':
      game_type = SNAKE;
      break;
    case '2':
      game_type = TETRIS;
      break;
    case '3':
      game_type = EXIT;
      break;
  }
  return game_type;
}