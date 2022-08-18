#include <chrono>
#include <iostream>
#include <thread>
#include <string>

#include "readerwriterqueue.h"

using namespace moodycamel;

class Worker {
 public:

  void Write() {
    std::string str("");
    int count = 10;
    int val = 0;
    while (true && count > 0) {
      // q.enqueue(val++);
      // std::this_thread::sleep_for(std::chrono::milliseconds(100));

      str = "No." + std::to_string(val) + "-";
      for (int i = 0; i < 10; ++i) {
        q.enqueue(str + std::to_string(i));
        std::cout << "++writer\t" << str + std::to_string(i) << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      ++val;
      --count;
    }
  }

  void Read() {
    std::string tmp;
    // while (true) {
    //   if (!q.try_dequeue(tmp)) {
    //     continue;
    //   }
    //   std::cout << "--reader\t"<<tmp << std::endl;
    //   std::this_thread::sleep_for(std::chrono::milliseconds(200));
    // }

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
  }

  private:
  BlockingReaderWriterQueue<std::string> q;
};


int main(void) {
  // 两个线程，一个线程写数据一个线程读数据
  // 预先分配内存
  //ReaderWriterQueue<int> q(10);
  //std::cout << q.max_capacity() << std::endl;

  int val = 0;
  
  std::string str("");
  Worker worker;
  std::thread writer(&Worker::Write, &worker);
  std::thread reader(&Worker::Read, &worker);

  writer.join();
  reader.join();

  return 0;
}