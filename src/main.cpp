// TODO <name>_hit and <name>_miss should return adress
// TODO Removing should be realized by lst.remove_if()
// TODO To figure out smth with the structure of cache
// TODO To realize normal data input
// TODO To realize config

#include <iostream>
#include <list>

namespace caches {

enum CacheTypes {
  LRU,
  FIFO
};

template <typename ValueT, typename KeyT = int> 
struct lru_cache {
  size_t cap_;
  std::list<ValueT> data_;

  bool is_full() const {
    return (data_.size() == cap_);
  }

  typename std::list<ValueT>::iterator get(KeyT key);


  lru_cache(size_t cap) : cap_(cap) {
    // не доделанный конструктор, жалуется на неинициализированный data_
    // по идее просто добавь в list-initializer сверху -leo
  }
};

template <typename ValueT, typename KeyT>
typename std::list<ValueT>::iterator 
lru_cache<ValueT, KeyT>::get(KeyT key) {
  return data_.begin(); // ? wrong implementation ? -leo
}

}
/*
void printList(std::list<int>& myList);
int is_cache_hit(std::list<int>& list, int value);
std::list<int>::iterator lru_cache(std::list<int>& list, int value);
void lru_hit(std::list<int>& list, int value);
void lru_miss(std::list<int>& list, int value);
std::list<int>::iterator fifo_cache(std::list<int>&list, int value);
void fifo_miss(std::list<int>& list, int value);
*/

int main() {
  size_t n = 0, m = 0;
  int value = 0;

  std::cin >> m >> n;
  caches::lru_cache<int> c{m};

  for (size_t i = 0; i < n; i++) {
    std::cin >> value;
    c.get(value);
  }
  return 0;
}

/*
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
*/
