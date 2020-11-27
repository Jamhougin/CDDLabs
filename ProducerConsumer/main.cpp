#include "Semaphore.h"
#include "SafeBuffer.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 10;
const int size = 10;
int num = 0;

/*! \fn producer
    \brief Creates events and adds them to buffer
*/

void producer(std::shared_ptr<Buffer> theBuffer, std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> consume){

  mutex->Wait();
  num = num + 10;
  std::cout << "Adding" << num << std::endl;
  theBuffer->enqueue(num);
  std::cout << "Added" << theBuffer->viewBack() << std::endl;
  mutex->Signal();
  consume->Signal();
}

/*! \fn consumer
    \brief Takes events from buffer and consumes them
*/

void consumer(std::shared_ptr<Buffer> theBuffer, std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> consume){

  consume->Wait();
  mutex->Wait();
  std::cout << "Removing" << theBuffer->viewFront() << std::endl;
  theBuffer->dequeue();
  mutex->Signal();
}

int main(void){

  std::vector<std::thread> pt(num_threads);
  std::vector<std::thread> ct(num_threads);
  std::shared_ptr<Buffer> aBuffer (new Buffer());
  std::shared_ptr<Semaphore> mutex (new Semaphore(1));
  std::shared_ptr<Semaphore> consume (new Semaphore(0)); 
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: pt){
    t=std::thread(producer, aBuffer, mutex, consume);
  }
  for(std::thread& t: ct){
    t=std::thread(consumer, aBuffer, mutex, consume);
  }
  /**< Join the threads with the main thread */
  for (auto& p :pt){
      p.join();
  }
  for (auto& p :ct){
      p.join();
  }
  std::cout << num << std::endl;
  return 0;
}
