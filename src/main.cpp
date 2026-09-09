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

int *lru_cache(std::list<int>& list, int value) {
  int is_hit = is_cache_hit(list, value);

  if (is_hit != NULL)
    return NULL;


  return NULL;
}

int main() {
/*
  std::cout << "Hello World!" << std::endl;
  std::list myList{10, 5, 5, 3, 1, -1, 4, 5, 6};
  printList(myList);

  myList.push_back(100);
  myList.push_front(300);
  printList(myList);

  myList.erase(myList.begin());
  printList(myList);

  std::list<int>::iterator itBegin = myList.begin();
  std::list<int>::iterator itEnd = myList.begin();
  std::advance(itBegin, 3);
  std::advance(itEnd, 9);
  myList.erase(itBegin, itEnd);
  printList(myList);
  return 0;
*/

  std::list myList{10, 5, 5, 3, 1, -1, 4, 5, 6};
  int x = is_cache_hit(myList, 100);

  std::cout << x << std::endl;

  return 0;
}

void printList(std::list<int>& myList) {
  for (int i : myList)
    std::cout << i << ' ';
  std::cout << std::endl;
}
