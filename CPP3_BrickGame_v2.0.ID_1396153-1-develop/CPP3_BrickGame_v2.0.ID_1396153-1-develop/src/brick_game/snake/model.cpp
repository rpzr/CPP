#include "model.h"

Model::Model()
    : currentState_(START_STATE),
      speed_(1),
      level_(1),
      score_(0),
      high_score_(0) {
  field_ = new int*[HEIGHT];
  for (size_t y = 0; y < HEIGHT; ++y) {
    field_[y] = new int[WIDTH]();
  }

  std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Model::~Model() {
  for (size_t y = 0; y < HEIGHT; ++y) {
    delete[] field_[y];
  }
  delete[] field_;
}

void Model::initializeGame() {
  snakeCoords.clear();
  speed_ = 1;
  level_ = 1;
  score_ = 0;
  high_score_ = 0;  // need to fix (from file)
  move_timer_ = 10;
  currentDirection = Right;
  boosted_speed_ = 8;
  snakeCoords.push_back({HEIGHT / 2, WIDTH / 2});
  snakeCoords.push_back({HEIGHT / 2, WIDTH / 2 - 1});
  snakeCoords.push_back({HEIGHT / 2, WIDTH / 2 - 2});
  snakeCoords.push_back({HEIGHT / 2, WIDTH / 2 - 3});
  generateFood();
  updateField();
}

void Model::fsmProc(UserAction_t action, bool hold) {
  switch (currentState_) {
    case START_STATE:
    case WIN_STATE:
      if (action == Start) {
        initializeGame();
        currentState_ = MOVING_STATE;
      }
      if (action == Terminate) {
        currentState_ = GAMEOVER_STATE;
      }
      break;
    case MOVING_STATE:
      processPlayingState(action);
      if (--move_timer_ <= 0) {
        moveSnake();
        resetMoveTimer(hold ? boosted_speed_ : speed_);
        if (checkCollision()) {
          currentState_ = GAMEOVER_STATE;
          if (score_ > high_score_) high_score_ = score_;
        }
      }
      updateField();
      break;
    case FREEZE_STATE:
      processPausedState(action);
      break;
    case GAMEOVER_STATE:
      processGameOverState(action);
      break;
    case SPAWN_STATE:
    case REACH_STATE:
    case EXIT_STATE:
    default:
      break;
  }
}

void Model::processPlayingState(UserAction_t action) {
  switch (action) {
    case Left:
    case Right:
    case Up:
    case Down:
      if (!((currentDirection == Left && action == Right) ||
            (currentDirection == Right && action == Left) ||
            (currentDirection == Up && action == Down) ||
            (currentDirection == Down && action == Up))) {
        currentDirection = action;
      }
      break;
    case Pause:
      currentState_ = FREEZE_STATE;
      break;
    case Terminate:
      currentState_ = EXIT_STATE;
    default:
      break;
  }
}

void Model::resetMoveTimer(int actual_speed) {
  move_timer_ = 10 - actual_speed;
}

void Model::processPausedState(UserAction_t action) {
  if (action == Pause) {
    currentState_ = MOVING_STATE;
  } else if (action == Terminate) {
    currentState_ = GAMEOVER_STATE;
  }
}

void Model::processGameOverState(UserAction_t action) {
  if (action == Start) {
    currentState_ = START_STATE;
  } else if (action == Terminate) {
    currentState_ = EXIT_STATE;
  }
}

void Model::moveSnake() {
  auto head = snakeCoords.front();
  switch (currentDirection) {
    case Left:
      head.second--;
      break;
    case Right:
      head.second++;
      break;
    case Up:
      head.first--;
      break;
    case Down:
      head.first++;
      break;
    default:
      break;
  }

  snakeCoords.push_front(head);

  if (head == food) {
    score_ += 1;
    if (score_ % 5 == 0 && speed_ < 10) {
      level_++;
      speed_++;
    }
    generateFood();
  } else {
    snakeCoords.pop_back();
  }
}

bool Model::checkCollision() {
  const auto& head = snakeCoords.front();

  if (head.first < 0 || head.first >= HEIGHT || head.second < 0 ||
      head.second >= WIDTH) {
    return true;
  }

  for (auto it = snakeCoords.begin() + 1; it != snakeCoords.end(); ++it) {
    if (*it == head) return true;
  }

  return false;
}

void Model::generateFood() {
  int attempts = 0;
  const int max_attempts = WIDTH * HEIGHT;

  while (attempts++ < max_attempts) {
    int x = std::rand() % WIDTH;
    int y = std::rand() % HEIGHT;

    bool onSnake = false;
    for (const auto& seg : snakeCoords) {
      if (seg.first == y && seg.second == x) {
        onSnake = true;
        break;
      }
    }

    if (!onSnake) {
      food = {y, x};
      return;
    }
  }

  currentState_ = WIN_STATE;
}

void Model::updateField() {
  for (size_t y = 0; y < HEIGHT; ++y) {
    for (size_t x = 0; x < WIDTH; ++x) {
      field_[y][x] = Empty;
    }
  }

  for (const auto& seg : snakeCoords) {
    if (seg.first >= 0 && seg.first < HEIGHT && seg.second >= 0 &&
        seg.second < WIDTH) {
      field_[seg.first][seg.second] = Body;
    }
  }

  if (food.first >= 0 && food.first < HEIGHT && food.second >= 0 &&
      food.second < WIDTH) {
    field_[food.first][food.second] = Food;
  }
}

GameInfo_t Model::getGameInfo() const {
  GameInfo_t state;
  state.field = field_;
  state.next = nullptr;
  state.score = score_;
  state.high_score = high_score_;
  state.level = level_;
  state.speed = speed_;
  state.pause = (currentState_ == FREEZE_STATE);
  return state;
}

GameState_t Model::getState() const { return currentState_; }
