#include <thread>
#include <mutex>
#include <iostream>

// unique_lock/lock_guard (since C++11)
// scoped_lock (since C++17)

int g_i = 0;
std::mutex g_mutex;

void safe_inc() {
  const std::lock_guard<std::mutex> lock(g_mutex);
  g_i++;

  std::cout << std::hex << std::this_thread::get_id() << ": " << g_i
            << std::endl;
  // g_mutex is automatically released when `lock` goes out of scope
}

int main(int argc, char **argv) {
  std::cout << "main: " << g_i << std::endl;

  std::thread t1(safe_inc);
  std::thread t2(safe_inc);

  t1.join();
  t2.join();

  std::cout << "main: " << g_i << std::endl;

  return 0;
}
