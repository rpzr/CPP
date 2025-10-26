#ifndef S21_MAP_METODS_H
#define S21_MAP_METODS_H

#include "s21_map.h"

namespace s21 {

// Вставка элемента в map
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  Node* dest = new Node(value);  // Создаем новый узел с переданным значением
  dest->color = COLOR_RED;  // Устанавливаем цвет узла в красный
  bool response = true;  // Флаг успешности вставки

  // Если дерево пустое, новый узел становится корнем
  if (root == nullptr) {
    root = dest;
  } else {
    Node* node = root;
    // Ищем место для вставки нового узла
    while (response) {
      if (node->value.first < value.first) {
        if (node->right_child) {
          node = node->right_child;
        } else {
          node->right_child = dest;
          dest->parent = node;
          break;
        }
      } else if (node->value.first > value.first) {
        if (node->left_child) {
          node = node->left_child;
        } else {
          node->left_child = dest;
          dest->parent = node;
          break;
        }
      } else {
        response = false;  // Ключ уже существует, вставка не удалась
        delete dest;
        dest = node;
      }
    }
  }

  // Если вставка прошла успешно, выполняем балансировку дерева
  if (response) {
    Node* tmp = dest;
    while (tmp->parent && tmp->parent->color == COLOR_RED) {
      Node* gdad = tmp->parent->parent;
      if (tmp->parent == gdad->left_child) {
        if (gdad->right_child && gdad->right_child->color == COLOR_RED) {
          gdad->color = COLOR_RED;
          gdad->right_child->color = COLOR_BLACK;
          gdad->left_child->color = COLOR_BLACK;
          tmp = gdad;
        } else {
          if (tmp->parent->right_child == tmp) {
            tmp = tmp->parent;
            tmp->left_rotate();
          }
          tmp->parent->color = COLOR_BLACK;
          tmp->parent->parent->color = COLOR_RED;
          tmp->parent->parent->right_rotate();
        }
      } else {
        if (gdad->left_child && gdad->left_child->color == COLOR_RED) {
          gdad->color = COLOR_RED;
          gdad->right_child->color = COLOR_BLACK;
          gdad->left_child->color = COLOR_BLACK;
          tmp = gdad;
        } else {
          if (tmp->parent->left_child == tmp) {
            tmp = tmp->parent;
            tmp->right_rotate();
          }
          tmp->parent->color = COLOR_BLACK;
          tmp->parent->parent->color = COLOR_RED;
          tmp->parent->parent->left_rotate();
        }
      }
    }
    root = tmp->root();
    root->color = COLOR_BLACK;
  }

  size_ += response;  // Увеличиваем размер дерева, если вставка прошла успешно
  return std::pair<typename map<Key, T>::iterator, bool>(
      MapIterator(dest, this),
      response);  // Возвращаем итератор и флаг успешности
}

// Удаление элемента из map
template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  Node* tbd = pos.node_;  // Узел, который нужно удалить
  Node* replacer = (tbd->right_child && tbd->left_child)
                       ? tbd->prev()
                       : tbd;  // Узел, который заменит удаляемый
  Node* replacer_child =
      (replacer->left_child)
          ? replacer->left_child
          : replacer->right_child;  // Наследник заменяющего узла
  bool plug_used = false;

  // Если у заменяющего узла нет наследников, создаем фиктивного наследника
  if (replacer_child == nullptr) {
    plug_used = true;
    replacer_child = new Node(replacer->value);
  }

  // Устанавливаем родителя для заменяющего наследника
  replacer_child->parent = replacer->parent;
  if (replacer->parent) {
    if (replacer == replacer->parent->left_child) {
      replacer->parent->left_child = replacer_child;
    } else {
      replacer->parent->right_child = replacer_child;
    }
  }

  // Если заменяющий узел не совпадает с удаляемым, копируем значения
  if (replacer != tbd) {
    const_cast<Key&>(tbd->value.first) = replacer->value.first;
    tbd->value.second = replacer->value.second;
  }

  // Балансировка дерева после удаления
  while (replacer->color == COLOR_BLACK && replacer_child->parent &&
         replacer_child->color == COLOR_BLACK) {
    if (replacer_child->parent->left_child == replacer_child) {
      Node* w = replacer_child->parent->right_child;
      if (w->color == COLOR_RED) {
        w->color = COLOR_BLACK;
        w->parent->color = COLOR_RED;
        replacer_child->parent->left_rotate();
        w = replacer_child->parent->right_child;
      }
      if (((!w->left_child || w->left_child->color == COLOR_BLACK) &&
           (!w->right_child || w->right_child->color == COLOR_BLACK))) {
        w->color = COLOR_RED;
        Node* tmp = replacer_child->parent;
        if (plug_used) {
          tmp->left_child = nullptr;
          delete replacer_child;
          plug_used = false;
        }
        replacer_child = tmp;
      } else {
        if (!w->right_child || w->right_child->color == COLOR_BLACK) {
          if (w->left_child) w->left_child->color = COLOR_BLACK;
          w->color = COLOR_RED;
          w->right_rotate();
          w = replacer_child->parent->right_child;
        }
        w->color = replacer_child->parent->color;
        replacer_child->parent->color = COLOR_BLACK;
        if (w->right_child) w->right_child->color = COLOR_BLACK;
        replacer_child->parent->left_rotate();
        break;
      }
    } else {
      Node* w = replacer_child->parent->left_child;
      if (w->color == COLOR_RED) {
        w->color = COLOR_BLACK;
        w->parent->color = COLOR_RED;
        replacer_child->parent->right_rotate();
        w = replacer_child->parent->left_child;
      }
      if ((!w->left_child || w->left_child->color == COLOR_BLACK) &&
          (!w->right_child || w->right_child->color == COLOR_BLACK)) {
        w->color = COLOR_RED;
        Node* tmp = replacer_child->parent;
        if (plug_used) {
          tmp->right_child = nullptr;
          delete replacer_child;
          plug_used = false;
        }
        replacer_child = tmp;
      } else {
        if (!w->left_child || w->left_child->color == COLOR_BLACK) {
          if (w->right_child) w->right_child->color = COLOR_BLACK;
          w->color = COLOR_RED;
          w->left_rotate();
          w = replacer_child->parent->left_child;
        }
        w->color = replacer_child->parent->color;
        replacer_child->parent->color = COLOR_BLACK;
        if (w->left_child) w->left_child->color = COLOR_BLACK;
        replacer_child->parent->right_rotate();
        break;
      }
    }
  }

  // Если заменяющий узел был черным, устанавливаем цвет наследника в черный
  if (replacer->color == COLOR_BLACK) replacer_child->color = COLOR_BLACK;

  size_--;  // Уменьшаем размер дерева
  root = (size_ != 0) ? replacer_child->root() : nullptr;  // Обновляем корень

  // Удаляем фиктивного наследника, если он был использован
  if (plug_used) {
    if (replacer_child->parent) {
      if (replacer_child->parent->left_child == replacer_child) {
        replacer_child->parent->left_child = nullptr;
      } else {
        replacer_child->parent->right_child = nullptr;
      }
    }
    delete replacer_child;
  }

  delete replacer;  // Удаляем заменяющий узел
}

// Метод at для доступа к элементу по ключу
template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  Node* node = root;
  while (node && node->value.first != key)
    node = (node->value.first < key) ? node->right_child : node->left_child;
  if (node == nullptr)
    throw std::out_of_range("There is no element with such key");
  return node->value.second;
}

// Метод find для поиска элемента по ключу
template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key& key) {
  Node* node = root;
  while (node && node->value.first != key)
    node = (node->value.first < key) ? node->right_child : node->left_child;
  return iterator(node, this);
}

// Метод для получения максимального размера map
template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

// Метод для вставки или присвоения значения по ключу
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  std::pair<typename map<Key, T>::iterator, bool> data = insert(key, obj);
  if (!data.second) (*(data.first)).second = obj;
  data.second = true;
  return data;
}

// Метод для вставки нескольких элементов
template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  return std::vector{insert(args)...};
}

// Метод для обмена содержимым двух map
template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  std::swap(other.root, root);
  std::swap(size_, other.size_);
}

// Метод для слияния двух map
template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  for (auto iter = other.begin(); iter != other.end(); ++iter) {
    insert(*iter);
  }
}

// Метод для проверки наличия элемента по ключу
template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) const {
  bool response = true;
  if (root == nullptr) response = false;
  Node* node = root;
  while (response) {
    if (node->value.first < key) {
      if (node->right_child) {
        node = node->right_child;
      } else {
        response = false;
      }
    } else if (node->value.first > key) {
      if (node->left_child) {
        node = node->left_child;
      } else {
        response = false;
      }
    } else
      break;
  }
  return response;
}

// Метод для очистки map
template <typename Key, typename T>
void map<Key, T>::clear() {
  if (root) root->destruct();
  size_ = 0;
  root = nullptr;
}

}  // namespace s21

#endif  // S21_MAP_METODS_H