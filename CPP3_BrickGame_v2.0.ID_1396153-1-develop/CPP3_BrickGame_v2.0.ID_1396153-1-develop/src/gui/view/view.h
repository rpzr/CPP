#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>

#include "../../brick_game/common/brickgame.h"

class GameWidget : public QGraphicsView {
  Q_OBJECT
 public:
  explicit GameWidget(QWidget* parent = nullptr);
  void draw(const GameInfo_t& info, GameState_t state);

 signals:
  void keyPressed(UserAction_t action);

 protected:
  void keyPressEvent(QKeyEvent* event) override;

 private:
  QGraphicsScene* scene;
  QGraphicsTextItem* scoreText;
  QGraphicsTextItem* stateText;
  QGraphicsRectItem* field[HEIGHT][WIDTH];
};

#endif  // VIEW_H