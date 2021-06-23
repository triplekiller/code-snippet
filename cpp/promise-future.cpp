#include <future>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// Future and Promise are the two separate sides of an asynchronous operation.

// std::promise is used by the "producer/writer" of the asynchronous operation.

// std::future is used by the "consumer/reader" of the asynchronous operation.

// The reason it is separated into these two separate "interfaces" is to hide
// the "write/set" functionality from the "consumer/reader".

// A std::future object can be used with asych, std::packaged_task and
// std::promise.

// std::promise is also a class template and its object promises to set the value
// in future. Each std::promise object has an associated std::future object that
// will give the value once set by the std::promise object.

// A std::promise object shares data with its associated std::future object.

void product(std::promise<int>&& intPromise, int a, int b) {
  intPromise.set_value(a * b);
}

struct Div{
  void operator() (std::promise<int>&& intPromise, int a, int b) const {
    intPromise.set_value(a / b);
  }
};

void sub_main() {
  int a= 20;
  int b= 10;

  std::cout << std::endl;

  // define the promises
  std::promise<int> prodPromise;
  std::promise<int> divPromise;

  // get the futures
  std::future<int> prodResult= prodPromise.get_future();
  std::future<int> divResult= divPromise.get_future();

  // calculate the result in a separat thread
  std::thread prodThread(product, std::move(prodPromise), a, b);

  Div div;
  std::thread divThread(div, std::move(divPromise), a, b);

  // get the result
  std::cout << "20*10= " << prodResult.get() << std::endl;
  std::cout << "20/10= " << divResult.get() << std::endl;

  prodThread.join();
  divThread.join();

  std::cout << std::endl;
}

void sub2_main() {
  std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
  std::shared_future<void> ready_future(ready_promise.get_future());

  std::chrono::time_point<std::chrono::high_resolution_clock> start;
 
  auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
  {
     t1_ready_promise.set_value();
     ready_future.wait(); // waits for the signal from main()
     return std::chrono::high_resolution_clock::now() - start;
  };
 
 
  auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli> 
  {
     t2_ready_promise.set_value();
     ready_future.wait(); // waits for the signal from main()
     return std::chrono::high_resolution_clock::now() - start;
  };
 
  auto fut1 = t1_ready_promise.get_future();
  auto fut2 = t2_ready_promise.get_future();
 
  auto result1 = std::async(std::launch::async, fun1);
  auto result2 = std::async(std::launch::async, fun2);
 
  // wait for the threads to become ready
  fut1.wait();
  fut2.wait();
 
  // the threads are ready, start the clock
  start = std::chrono::high_resolution_clock::now();
 
  // signal the threads to go
  ready_promise.set_value();
 
  std::cout << "Thread 1 received the signal "
            << result1.get().count() << " ms after start\n"
            << "Thread 2 received the signal "
            << result2.get().count() << " ms after start\n";
}

// g++ -std=c++11 promise-future.cpp -lpthread
int main() {
  auto promise = std::promise<std::string>();

  auto producer = std::thread([&] { promise.set_value("Hello World\n"); });

  auto future = promise.get_future();

  auto consumer = std::thread([&] { std::cout << future.get(); });

  producer.join();
  consumer.join();

  sub_main();

  sub2_main();

  return 0;
}
