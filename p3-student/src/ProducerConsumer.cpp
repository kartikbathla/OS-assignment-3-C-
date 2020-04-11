#include "ProducerConsumer.h"

// TODO: add BoundedBuffer, locks and any global variables here
BoundedBuffer buffer(5);
int prod_counter, con_counter, item_counter, p_sleep, c_sleep;
pthread_mutex_t p_lock;
pthread_mutex_t c_lock; 
pthread_mutex_t print_lock;
time_t start_time;
ofstream output_file;

void InitProducerConsumer(int p, int c, int psleep, int csleep, int items) {
  //TODO: constructor to initialize variables declared
  //also see instruction for implementation
  p_sleep = psleep*1000*1000;
  c_sleep = csleep*1000*1000;
  item_counter = items; 
  prod_counter = 0;
  con_counter = 0;

  output_file.open("output.txt");

  start_time = time(0);

  pthread_mutex_init(&p_lock, NULL);
  pthread_mutex_init(&c_lock, NULL);

  pthread_t* producer_arr, *consumer_arr;
  producer_arr = new pthread_t[p];
  consumer_arr = new pthread_t[c]; 
  
  for(int i = 0; i < p; i++)
  {
    int threadID = i;
    pthread_create(&producer_arr[i], NULL, producer, &threadID);
  }
  for(int i = 0; i < c; i++)
  {
    pthread_create(&consumer_arr[i], NULL, consumer, &i);
  }
  for(int i = 0; i < p; i++)
  {
    pthread_join(producer_arr[i], NULL);
  }
  for(int i = 0; i < c; i++)
  {
    pthread_join(consumer_arr[i], NULL);
  }
  output_file.close();
}

void* producer(void* threadID) {
  int threadNum = *((int*)threadID);
  //TODO: producer thread, see instruction for implementation
  while(prod_counter < item_counter){
		usleep(p_sleep);		
		int data = rand();
		pthread_mutex_lock(&p_lock);
		if(prod_counter == item_counter)
    {
      pthread_mutex_unlock(&p_lock);
			return NULL;
		}
		prod_counter++;
		pthread_mutex_unlock(&p_lock);
		buffer.append(data);
		pthread_mutex_lock(&print_lock);
		output_file << "Producer #" << to_string(threadNum) << ", time = " << start_time << ", producing data item #" << prod_counter << ", item value=" << data << endl;
    pthread_mutex_unlock(&print_lock);
	}
  return NULL;
}

void* consumer(void* threadID) {
  //TODO: consumer thread, see instruction for implementation
  int threadNum = *((int*)threadID);
  while(con_counter < item_counter){
		
		usleep(c_sleep);		
		pthread_mutex_lock(&c_lock);
		while(con_counter == item_counter){
			pthread_mutex_unlock(&c_lock);
			return NULL;
		}
		con_counter++;
		pthread_mutex_unlock(&c_lock);
		int data = buffer.remove();		
		pthread_mutex_lock(&print_lock);
		output_file << "Consumer #" << threadNum << ", time = " << start_time << ", consuming data item with value" << data << endl;
		pthread_mutex_unlock(&print_lock);
  }
  return NULL;
}
