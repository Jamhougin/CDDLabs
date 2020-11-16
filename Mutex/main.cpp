#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 1000;
int sharedVariable=0;


/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> mutSem, int numUpdates){

  
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    mutSem->Wait();
    sharedVariable++;
    mutSem->Signal();
  }
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aMutexSem( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aMutexSem,10000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
