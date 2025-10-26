#include "view.h"

GameWidget::GameWidget(QWidget* parent) : QGraphicsView(parent) {
  scene = new QGraphicsScene(this);
  setScene(scene);
  setFixedSize(600, 400);
  setFocusPolicy(Qt::StrongFocus);

  // Инициализация поля
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      field[y][x] = scene->addRect(x * 20, y * 20, 20, 20, QPen(Qt::gray),
                                   QBrush(Qt::white));
    }
  }

  // Текстовые элементы
  scoreText = scene->addText("Score: 0");
  scoreText->setPos(420, 20);
  scoreText->setFont(QFont("Courier", 12));

  stateText = scene->addText("Press Enter");
  stateText->setPos(420, 80);
  stateText->setFont(QFont("Courier", 12));
}

void GameWidget::draw(const GameInfo_t& info, GameState_t state) {
  // Отрисовка поля
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      QBrush brush(Qt::white);
      if (info.field[y][x] == Body)
        brush = Qt::blue;
      else if (info.field[y][x] == Food)
        brush = Qt::green;
      field[y][x]->setBrush(brush);
    }
  }

  // Обновление текста
  scoreText->setPlainText(QString("Score: %1\nHigh: %2\nLevel: %3")
                              .arg(info.score)
                              .arg(info.high_score)
                              .arg(info.level));

  stateText->setPlainText(state == START_STATE      ? "Press Enter"
                          : state == FREEZE_STATE   ? "PAUSED"
                          : state == GAMEOVER_STATE ? "GAME OVER"
                                                    : "");
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Up:
      emit keyPressed(Up);
      break;
    case Qt::Key_Down:
      emit keyPressed(Down);
      break;
    case Qt::Key_Left:
      emit keyPressed(Left);
      break;
    case Qt::Key_Right:
      emit keyPressed(Right);
      break;
    case Qt::Key_P:
      emit keyPressed(Pause);
      break;
    case Qt::Key_Space:
      emit keyPressed(Action);
      break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
      emit keyPressed(Start);
      break;
    case Qt::Key_Escape:
      emit keyPressed(Terminate);
      break;
    default:
      QGraphicsView::keyPressEvent(event);
  }
}