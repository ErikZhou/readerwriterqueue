#include <chrono>
#include <iostream>
#include <thread>

#include "readerwriterqueue.h"

using namespace moodycamel;
int main(void) {
  // �����̣߳�һ���߳�д����һ���̶߳�����
  // Ԥ�ȷ����ڴ�
  ReaderWriterQueue<int> q(10);
  std::cout << q.max_capacity() << std::endl;

  int val = 1;
  int count = 100;
  std::thread writer([&]() {
    while (true && count>0) {
      std::cout << "++writer\t" << val << "\n";
      q.enqueue(val++);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      --count;
    }
    });

  std::thread reader([&]() {
    int tmp;
    while (true) {
      if (!q.try_dequeue(tmp)) {
        continue;
      }
      std::cout << "--reader\t"<<tmp << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    });

  writer.join();
  reader.join();

  return 0;
}