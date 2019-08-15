#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "queue.h"
#include "file_monity.h"
#include "handle_data.h"
#include "SQLWork.h"
 

#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/thread.hpp>  
#include <boost/thread/thread_pool.hpp>  

using namespace std;  
#define MAX_QUEUE_LEN 200
queue_t * gQueue = NULL;

int do_file_monity_callback_ex(char *filename)
{
	if(gQueue){

		char * myFileName =(char *) malloc(strlen(filename)+1);
		memset(myFileName,0,strlen(filename)+1);
		memcpy(myFileName,filename,strlen(filename));
		printf("do_file_monity_callback_ex %s\n",filename);
		queue_put(gQueue,myFileName);
	}
	return 0;
}
void handle_file_data_task()  
{ 
	//get file name from queue
	char *myfilename = NULL;
	do{
		
		//printf("queue_get\n");
		if(queue_get(gQueue,(void**)&myfilename) < 0){
			boost::this_thread::sleep(boost::posix_time::millisec(200));
			
				//printf("handle_file_data_task\n");
			}
		else
			{
				if(myfilename)
					{
						handle_file(myfilename);
					}
			}
		myfilename = NULL;

	}while(1);
}


int main(int argc, char *argv[])
{
   
	boost::basic_thread_pool *tp;
	gQueue = queue_create( );
	if(!gQueue)
		return -1;

	SQLWork *myWork=new SQLWork("tcp://192.168.3.28:3306", "root", "root");
	if(myWork->doConnect()){
		cout<<"connect error"<<endl;;
		exit(-1); 
	}else
		{
		cout<<"connect database ok"<<endl;;
		}
	if(myWork->chooseDatabase("face_recognition")){
		cout<<"choose error"<<endl;
		exit(-1);
	}
//	if(myWork->changeCharacter("gbk")){
//			cout<<"change error"<<endl;
//			exit(-1);
//		}
/*	if(myWork->doWork()){
		cout<<"do work error"<<endl;;
		exit(-1);
	}*/

	tp = new boost::basic_thread_pool(8);

	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);
	tp->submit(&handle_file_data_task);

	do_file_monity("/root",do_file_monity_callback_ex);

    return 0;
}
