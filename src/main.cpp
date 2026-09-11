// TODO <name>_hit and <name>_miss should return adress
// TODO Removing should be realized by lst.remove_if()
// TODO To figure out smth with the structure of cache
// TODO To realize normal data input
// TODO To realize config

#include <iostream>
#include <list>

struct Cache {
  std::list<int> data;
  std::list<int> freq;
};

void printList(std::list<int>& myList);
int is_cache_hit(std::list<int>& list, int value);
std::list<int>::iterator lru_cache(std::list<int>& list, int value);
void lru_hit(std::list<int>& list, int value);
void lru_miss(std::list<int>& list, int value);
std::list<int>::iterator fifo_cache(std::list<int>&list, int value);
void fifo_miss(std::list<int>& list, int value);

int main() {
  std::list<int> myList(5);
  int value;

  for (int i = 0; i < 10; i++) {
    std::cin >> value;
    fifo_cache(myList, value);
    printList(myList);
  }
  return 0;
}

void printList(std::list<int>& list) {
  for (int i : list)
    std::cout << i << ' ';
  std::cout << std::endl;
}

int is_cache_hit(std::list<int>& list, int value) {
  for (int i : list) {
    if (i == value) {
      return 1;
    }
  }
  return 0;
}

std::list<int>::iterator lru_cache(std::list<int>& list, int value) {
  int is_hit = is_cache_hit(list, value);

  if (is_hit) {
    lru_hit(list, value);
  } else {
    lru_miss(list, value);
  }

  return list.begin();
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

void lru_miss(std::list<int>& list, int value) {
  list.push_front(value);
  list.pop_back();
}

std::list<int>::iterator fifo_cache(std::list<int>&list, int value) {
  int is_hit = is_cache_hit(list, value);

  if (!is_hit)
    fifo_miss(list, value);

  for (auto it = list.begin(); it != list.end(); it++) {
    if (*it == value)
      return it;
  }
}

void fifo_miss(std::list<int>& list, int value) {
  list.push_front(value);
  list.pop_back();
}