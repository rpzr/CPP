#include <QApplication>
#include <QInputDialog>
#include <QMainWindow>
#include <QTimer>

#include "../gui/view/view.h"
#include "./snake/controller.h"
#include "./tetris/backend.h"

int showMainMenu(QWidget* parent = nullptr) {
  bool ok;
  int result =
      QInputDialog::getItem(parent, "Choose Game", "Select a game:",
                            QStringList() << "SNAKE" << "TETRIS" << "EXIT", 0,
                            false, &ok)
          .toInt();
  return ok ? result : EXIT;
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  int selected;
  while ((selected = showMainMenu()) != EXIT) {
    QMainWindow window;
    selected = TETRIS;
    window.setWindowTitle(selected == SNAKE ? "Snake" : "Tetris");

    GameWidget* gameWidget = new GameWidget();
    window.setCentralWidget(gameWidget);
    window.resize(600, 400);
    window.show();
    gameWidget->setFocus();

    Controller* controller = nullptr;
    if (selected == SNAKE) {
      static Model model;
      static Controller snakeController(model);
      controller = &snakeController;
      model.initializeGame();
    } else {
      initGame(getTetrisGame());
    }

    QTimer gameTimer;
    int frameCounter = 0;

    QObject::connect(&gameTimer, &QTimer::timeout, [&]() {
      frameCounter++;

      if (selected == SNAKE) {
        UserAction_t dir = controller->getCurrentDirection();
        controller->userInput(dir, false);
      } else {
        userInput(Up, false);
      }

      GameInfo_t info = selected == SNAKE ? controller->updateCurrentState()
                                          : updateCurrentState();

      GameState_t state =
          selected == SNAKE ? controller->getGameState() : getState();

      gameWidget->draw(info, state);

      if (state == GAMEOVER_STATE || state == EXIT_STATE) {
        gameTimer.stop();
      }
    });

    QObject::connect(gameWidget, &GameWidget::keyPressed,
                     [&](UserAction_t action) {
                       if (selected == SNAKE) {
                         controller->userInput(action, action == Action);
                       } else {
                         userInput(action, action == Action);
                       }

                       if (action == Start && !gameTimer.isActive()) {
                         gameTimer.start(50);
                       }
                     });

    gameTimer.start(50);
    app.exec();
    delete gameWidget;
  }

  return 0;
}