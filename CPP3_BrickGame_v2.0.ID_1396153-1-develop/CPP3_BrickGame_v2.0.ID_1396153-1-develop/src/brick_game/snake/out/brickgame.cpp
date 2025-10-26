#include "../gui/cli/frontend.h"
#include "./snake/controller.h"
#include "./snake/model.h"
#include "./tetris/inc/backend.h"

#define MENU_WIDTH 30
#define MENU_HEIGHT 10

void show_menu(WINDOW *menu_win, int highlight) {
  const char *choices[] = {"1. Tetris", "2. Snake", "3. Exit"};
  int n_choices = sizeof(choices) / sizeof(char *);

  box(menu_win, 0, 0);
  mvwprintw(menu_win, 1, 1, "BRICK GAME");
  mvwprintw(menu_win, 2, 1, "Select game:");

  for (int i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, i + 4, 2, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, i + 4, 2, "%s", choices[i]);
    }
  }
  wrefresh(menu_win);
}

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  int startx = (COLS - MENU_WIDTH) / 2;
  int starty = (LINES - MENU_HEIGHT) / 2;

  WINDOW *menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
  int highlight = 1;
  int choice = 0;

  while (1) {
    show_menu(menu_win, highlight);
    int c = getch();

    switch (c) {
      case KEY_UP:
        if (highlight == 1)
          highlight = 3;
        else
          --highlight;
        break;
      case KEY_DOWN:
        if (highlight == 3)
          highlight = 1;
        else
          ++highlight;
        break;
      case 10:  // Enter
        choice = highlight;
        break;
      default:
        break;
    }

    if (choice != 0) {
      werase(menu_win);
      wrefresh(menu_win);
      delwin(menu_win);

      switch (choice) {
        case 1: {  // Tetris
          bool isPlaying = TRUE;

          while (isPlaying) {
            UserAction_t act = ProcessInput();
            userInput(act, FALSE);
            GameInfo_t info = updateCurrentState();
            GameState_t state = getState();

            if (state == EXIT_STATE) {
              isPlaying = FALSE;
            }

            RenderGameScreen(&info, state);
            usleep(DELAY_MS * 1000);
          }
          break;
        }
        case 2: {  // Snake
          Model model;
          Controller controller(model);
          bool isPlaying = TRUE;

          while (isPlaying) {
            UserAction_t act = ProcessInput();
            controller.userInput(act, FALSE);
            GameInfo_t game = controller.updateCurrentState();
            GameState_t state = controller.getGameState();

            if (state == EXIT_STATE) {
              isPlaying = FALSE;
            }

            RenderGameScreen(&game, state);
            usleep(DELAY_MS * 1000);
          }
          break;
        }
        case 3:  // Exit
          endwin();
          return 0;
      }

      // После выхода из игры возвращаемся в меню
      refresh();
      clear();
      menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
      highlight = 1;
      choice = 0;
    }
  }

  endwin();
  return 0;
}