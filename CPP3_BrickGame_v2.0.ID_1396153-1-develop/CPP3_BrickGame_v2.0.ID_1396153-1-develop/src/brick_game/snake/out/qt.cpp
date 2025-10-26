#include <QApplication>

#include "../../gui/view/view.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  GameView gameView;
  gameView.setWindowTitle("Snake Game");
  gameView.show();

  return app.exec();
}