#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
	//DEBUG_LOG("Starting thread...\n");
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    int rc = 0;
    struct thread_data *data = (struct thread_data *)thread_param;
    
	//waiting before to attempt to lock the mutex
	usleep(data->wait_to_obtain_ms*1000);

	rc = pthread_mutex_lock(data->mutex);
	if(rc != 0){
		//DEBUG_LOG("pthread_mutex_lock failed with %d\n", rc);
		data->thread_complete_success = false;
		return data;
	}
	//DEBUG_LOG("Thread %lu has obtained the mutex\n", *(data->thread));
	
	//waiting before to release the mutex
	usleep(data->wait_to_release_ms*1000);
	
	rc = pthread_mutex_unlock(data->mutex);
	if(rc != 0){
		//DEBUG_LOG("pthread_mutex_unlock failed with %d\n", rc);
		data->thread_complete_success = false;
		return data;
	}
	
	//DEBUG_LOG("Thread %lu returning data pointer: %p\n", *(data->thread), data);
	data->thread_complete_success = true;
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    //allocate memory for thread_data structure
    DEBUG_LOG("Allocate memory for structure...\n");
    struct thread_data *data = (struct thread_data*)malloc(sizeof(struct thread_data));
    if(!data){
    	perror("Cannot allocate memory for thread_data");
    	return false;
    }
    
    //initialize data
    data->thread_complete_success = false;
    data->mutex = mutex;
    data->wait_to_obtain_ms = wait_to_obtain_ms;
    data->wait_to_release_ms = wait_to_release_ms;
    
    // create the thread
    DEBUG_LOG("Creating thread...\n");
    if(pthread_create(thread, NULL, threadfunc, data) != 0){
    	free(data);
    	return false;
    }

    return true;
}
