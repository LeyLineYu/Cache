#include <iostream>
#include <list>

void printList(std::list<int>& myList);

int is_cache_hit(std::list<int>& list, int value) {
  for (int i : list) {
    if (i == value) {
      return 1;
    }
  }
  return 0;
}

void lru_miss(std::list<int>& list, int value) {
  list.push_front(value);
  list.pop_back();
}

void lru_hit(std::list<int>& list, int value) {
  if (*list.begin() == value)
    return;

  list.push_front(value);

  for (auto it = ++list.begin(); it != list.end(); it++) {
    if (*it == value) {
      list.erase(it);
      break;
    }
  }
}

auto lru_cache(std::list<int>& list, int value) {
  int is_hit = is_cache_hit(list, value);

  if (is_hit) {
    lru_hit(list, value);
  } else {
    lru_miss(list, value);
  }

  return list.begin();
}

int main() {
  std::list myList{1, 2, 3, 4, 5};
  int value;

  for (int i = 0; i < 10; i++) {
    std::cin >> value;
    auto x = lru_cache(myList, value);
    printList(myList);
  }
  return 0;
}

void printList(std::list<int>& list) {
  for (int i : list)
    std::cout << i << ' ';
  std::cout << std::endl;
}
