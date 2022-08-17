#include <chrono>
#include <iostream>
#include <thread>
#include <string>

#include "readerwriterqueue.h"

using namespace moodycamel;
int main(void) {
  // 两个线程，一个线程写数据一个线程读数据
  // 预先分配内存
  //ReaderWriterQueue<int> q(10);
  BlockingReaderWriterQueue<std::string> q;
  std::cout << q.max_capacity() << std::endl;

  int val = 0;
  int count = 10;
  std::string str("");
  std::thread writer([&]() {
    while (true && count > 0) {
      
      //q.enqueue(val++);
      //std::this_thread::sleep_for(std::chrono::milliseconds(100));

      str = "No." + std::to_string(val) + "-";
      for (int i = 0; i < 10; ++i) {
        q.enqueue(str + std::to_string(i));
        std::cout << "++writer\t" << str + std::to_string(i) << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      ++val;
      --count;
    }
    });

  std::thread reader([&]() {

    std::string tmp;
    //while (true) {
    //  if (!q.try_dequeue(tmp)) {
    //    continue;
    //  }
    //  std::cout << "--reader\t"<<tmp << std::endl;
    //  std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //}

    //
#if 1
   // for (int i = 0; i != 100; ++i) {
      // Fully-blocking:
    while (true) {
      q.wait_dequeue(tmp);
      std::cout << "--reader\t" << tmp << std::endl;
    }
    //}
#else
    while (true) {
      // Blocking with timeout
      if (q.wait_dequeue_timed(tmp, std::chrono::milliseconds(5))) {
        std::cout << "--reader\t" << tmp << std::endl;
      }
    }

#endif
    });

  writer.join();
  reader.join();

  return 0;
}